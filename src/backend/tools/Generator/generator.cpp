#include "generator.h"
#include <QCoreApplication>
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent)
{
    initParameters();
    parseWebsiteIndexFile();
    generateWebroot();
    qDebug()<<"finish";
    exit(0);
}

void Generator::initParameters()
{
    QStringList parametersList = QCoreApplication::arguments();
    foreach(QString parameter,parametersList)
    {
        QStringList tmpList = parameter.split('=');
        m_paramenters.insert(tmpList[0],tmpList.size()>1?tmpList[1]:QString(""));
    }
    if(m_paramenters.contains("--version"))
    {
        std::cout<<"Labrador Parser Version "<<BASE_VERSION<<std::endl;
    }
    if(!m_paramenters.contains("--index-file"))
    {
        std::cerr<<"index file can't be empty, generator will exit now!"<<std::endl;
        exit(0);
    }
    else
    {
        m_indexFilePath = m_paramenters.value("--index-file");
    }
    if(!m_paramenters.contains("--webroot-dir"))
    {
        std::cerr<<"webroot dir can't be empty, generator will exit now!"<<std::endl;
        exit(0);
    }
    else
    {
        m_webrootDir.mkpath(m_paramenters.value("--webroot-dir"));
        m_webrootDir.cd(m_paramenters.value("--webroot-dir"));
    }
    if(m_paramenters.contains("--log-file"))
    {
        YZLogger::logFilePath = m_paramenters.value("--log-file");
    }
}

void Generator::parseWebsiteIndexFile()
{
    QFile indexFile(m_indexFilePath);
    if (!indexFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr<<"can't open index file"<<std::endl;
        exit(0);
    }
    xmlReader.setDevice(&indexFile);
    while (!xmlReader.atEnd()) {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name()=="website")
                parseWebsiteXml(xmlReader);
            else
            {
                qWarning()<<"invalid xml format";
            }
        }
        xmlReader.readNext();
    }
    indexFile.close();
}

void Generator::parseWebsiteXml(QXmlStreamReader &reader)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="website")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="info")
            {
                m_website.info = reader.readElementText();
            }
            else if(reader.name()=="node")
            {
                parseNodeXml(reader,m_website.node);
            }
        }
        reader.readNext();
    }
}

void Generator::parseNodeXml(QXmlStreamReader &reader, Node &node)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="node")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="name")
            {
                node.name = reader.readElementText();
            }
            else if(reader.name()=="url")
            {
                node.url = reader.readElementText();
            }
            else if(reader.name()=="hashName")
            {
                node.hashName = reader.readElementText();
            }
            else if(reader.name()=="level")
            {
                node.level = reader.readElementText();
            }
            else if(reader.name()=="nodeList")
            {
                parseNodeListXml(reader,node);
            }
        }
        reader.readNext();
    }
}

void Generator::parseNodeListXml(QXmlStreamReader &reader, Node &node)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="nodeList")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="node")
            {
                Node newNode;
                newNode.parentNode = &node;
                node.nodeList<<newNode;
                parseNodeXml(reader,node.nodeList.last());
            }
        }
        reader.readNext();
    }
}

void Generator::generateWebroot()
{
    m_webrootDir.mkpath(m_webrootDir.absolutePath()+"/a");
    m_webrootDir.mkpath(m_webrootDir.absolutePath()+"/l");
    m_webrootDir.mkpath(m_webrootDir.absolutePath()+"/c");
    generateIndexFile();
    generateFiles();
}

void Generator::generateIndexFile()
{
    QFile file(m_webrootDir.absolutePath()+"/index.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning()<<"can't open index xml file";
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("website");
    writer.writeTextElement("name",m_website.node.name);
    writer.writeTextElement("info",m_website.info);
    writer.writeTextElement("url",m_website.node.url);
    writer.writeStartElement("nodeList");
    for(int i=0;i<m_website.node.nodeList.size();i++)
    {
        const Node &node = m_website.node.nodeList[i];
        writer.writeStartElement("indexNode");
        writer.writeStartElement("node");
        writer.writeTextElement("name",node.name);
        writer.writeTextElement("url",node.url);
        if(node.level.isEmpty ())
        {
            writer.writeTextElement ("level","0000");
        }
        else
        {
            writer.writeTextElement ("level",node.level);
        }
        NodeType type = getNodeType(node);

        if(type==ArticleNode)
        {
            node.pageUrl = "./a/"+node.hashName.left(2)+"/"+ node.hashName+".xml";
        }
        else if(type==ListNode)
        {
            node.pageUrl = "./l/"+ node.hashName+".xml";
        }
        else
        {
            node.pageUrl = "./c/"+ node.hashName+".xml";
        }

        writer.writeTextElement("pageUrl",node.pageUrl);
        m_nodeStack.push(&node);
        writer.writeEndElement();
        if(getNodeType(node)!=ArticleNode)
        {
            writer.writeStartElement("nodeList");
            const QList<Node> &nodeList = node.nodeList;
            foreach(Node node, nodeList)
            {
                writer.writeStartElement("node");
                writer.writeTextElement("name",node.name);
                writer.writeTextElement("url",node.url);
                if(node.level.isEmpty ())
                {
                    writer.writeTextElement ("level","0000");
                }
                else
                {
                    writer.writeTextElement ("level",node.level);
                }
                NodeType type = getNodeType(node);

                if(type==ArticleNode)
                {
                    node.pageUrl = "./a/"+node.hashName.left(2)+"/"+ node.hashName+".xml";
                }
                else if(type==ListNode)
                {
                    node.pageUrl = "./l/"+ node.hashName+".xml";
                }
                else
                {
                    node.pageUrl = "./c/"+ node.hashName+".xml";
                }

                writer.writeTextElement("pageUrl",node.pageUrl);

                writer.writeEndElement();
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void Generator::writeNodeXml(QXmlStreamWriter &writer, const Node &node)
{
    writer.writeStartElement("node");
    writer.writeTextElement("name",node.name);
    writer.writeTextElement("url",node.url);
    if(node.level.isEmpty ())
    {
        writer.writeTextElement ("level","0000");
    }
    else
    {
        writer.writeTextElement ("level",node.level);
    }
    NodeType type = getNodeType(node);

    if(type==ArticleNode)
    {
        node.pageUrl = "../a/"+node.hashName.left(2)+"/"+ node.hashName+".xml";
    }
    else if(type==ListNode)
    {
        node.pageUrl = "../l/"+ node.hashName+".xml";
    }
    else
    {
        node.pageUrl = "../c/"+ node.hashName+".xml";
    }

    writer.writeTextElement("pageUrl",node.pageUrl);

    m_nodeStack.push(&node);

    writer.writeEndElement();
}

void Generator::writeNodeListXml(QXmlStreamWriter &writer, const QList<Node> &nodeList)
{
    writer.writeStartElement("nodeList");
    for(int i=0;i<nodeList.size();i++)
    {
        writeNodeXml(writer,nodeList[i]);
    }
    writer.writeEndElement();
}

NodeType Generator::getNodeType(const Node &node)
{
    NodeType type;
    if(node.nodeList.isEmpty())
    {
        type=ArticleNode;
    }
    else if(node.nodeList[0].nodeList.isEmpty())
    {
        type=ListNode;
    }
    else
    {
        type= ColumnNode;
    }
    return type;
}

void Generator::generateFiles()
{
    while(!m_nodeStack.isEmpty())
    {
        const Node *tmpNode = m_nodeStack.pop();
        NodeType type = getNodeType(*tmpNode);

        if(type==ListNode)
        {
            generateListFile(*tmpNode);
        }
        else if(type == ColumnNode)
        {
            generateColumnFile(*tmpNode);
        }
        else if(type == ArticleNode)
        {
            generateArticleFile(*tmpNode);
        }
        else
        {

        }


    }
}

//20130428
QString Generator::generatePageTitle(const Node &node)
{

    QString ptitle="ptitle";
    QFile file;
    file.setFileName(m_webrootDir.absolutePath()+"/../parser/"+node.hashName.left(2)+"/"+node.hashName+".xml");    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr<<"can't open index file"<<std::endl;
        return ptitle;
    }
    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        xmlReader.readNext();
        if(xmlReader.name()=="ptitle")
         ptitle = xmlReader.readElementText();
    }
    file.close();
    return ptitle;
}





void Generator::generateColumnFile(const Node &node)
{
    QFile file;
    file.setFileName(m_webrootDir.absolutePath()+"/c/"+node.hashName+".xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        std::cerr<<"can't write webroot column file"<<std::endl;
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("column");
//20130428
    QString ptitle="C";
    ptitle=generatePageTitle(node);
    writer.writeTextElement("ptitle",ptitle);      

    writer.writeTextElement("name",node.name);
    writer.writeTextElement("url",node.url);
    writeParentPageUrlXml(writer,node);
    writeNodeListXml(writer,node.nodeList);
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void Generator::generateListFile(const Node &node)
{
    QFile file;
    file.setFileName(m_webrootDir.absolutePath()+"/l/"+node.hashName+".xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        std::cerr<<"can't write webroot column file"<<std::endl;
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("list");
//20130428
    QString ptitle="L";
    ptitle=generatePageTitle(node);
    writer.writeTextElement("ptitle",ptitle);      

    writer.writeTextElement("name",node.name);
    writer.writeTextElement("url",node.url);
    writeParentPageUrlXml(writer,node);
    writeNodeListXml(writer,node.nodeList);
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void Generator::generateArticleFile(const Node &node)
{
    QFile file;
    m_webrootDir.mkpath(m_webrootDir.absolutePath()+"/a/"+node.hashName.left(2));
    file.setFileName(m_webrootDir.absolutePath()+"/a/"+node.hashName.left(2)+"/"+ node.hashName+".xml");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        std::cerr<<"can't write webroot article file"<<std::endl;
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writeParentPageUrlXml(writer,node);
    writer.writeEndDocument();
    file.close();
}

void Generator::writeParentPageUrlXml(QXmlStreamWriter &writer, const Node &nodeItem)
{
    //article need to add ../../ to the pageUrl
    QString articlePageUrlPrefix = getNodeType(nodeItem)==ArticleNode?"../":"";
    writer.writeStartElement("parentPageUrl");
    Node *node = &(const_cast<Node &>(nodeItem));
    QStack<Node *> nodeStack;
    while(node->parentNode!=NULL)
    {
        nodeStack.push(node);
        node= node->parentNode;
    }
    while(!nodeStack.isEmpty())
    {
        node=nodeStack.pop();
        writer.writeStartElement("node");
        writer.writeTextElement("name",node->parentNode->name);
        // node is direct child of website
        if(node->parentNode==&m_website.node)
        {
            writer.writeTextElement("pageUrl",articlePageUrlPrefix+"../index.xml");
        }
        //because index.xml is not in c folder :)
        //direct children of index.xml
        else if(node->parentNode->parentNode!=NULL&&node->parentNode->parentNode==&m_website.node)
        {
            writer.writeTextElement("pageUrl",articlePageUrlPrefix+"."+node->parentNode->pageUrl);
        }
        //other nodes
        else
        {
            writer.writeTextElement("pageUrl",articlePageUrlPrefix+node->parentNode->pageUrl);
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();
}
