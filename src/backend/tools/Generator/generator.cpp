#include "generator.h"
#include <QCoreApplication>
#include <QDebug>

Generator::Generator(QObject *parent) :
    QObject(parent)
{
    initParameters();
    parseWebsiteIndexFile();
    generateWebroot();
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
    qDebug()<<"finish";
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
            if(reader.name()=="editor")
            {
                m_website.editor = reader.readElementText();
            }
            else if(reader.name()=="info")
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
                node.pageUrl = reader.readElementText();
            }
            else if(reader.name()=="nodeList")
            {
                parseNodeListXml(reader,node.nodeList);
            }
        }
        reader.readNext();
    }
}

void Generator::parseNodeListXml(QXmlStreamReader &reader, QList<Node> &nodeList)
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
                nodeList<<newNode;
                parseNodeXml(reader,nodeList.last());
            }
        }
        reader.readNext();
    }
}

void Generator::generateWebroot()
{
    generateIndexFile();
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
    writer.writeTextElement("editor",m_website.editor);
    writer.writeTextElement("info",m_website.info);
    writeNodeListXml(writer,m_website.node.nodeList);
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void Generator::writeNodeXml(QXmlStreamWriter &writer, Node &node)
{
    writer.writeStartElement("node");
    writer.writeTextElement("name",node.name);
    writer.writeTextElement("url",node.url);
    NodeType type = getNodeType(node);
    if(type==ArticleNode)
    {
        writer.writeTextElement("pageUrl","../a/"+node.pageUrl.left(2)+"/"+ node.pageUrl);
    }
    else if(type==ListNode)
    {
        writer.writeTextElement("pageUrl","../l/" + node.pageUrl);
    }
    else
    {
       writer.writeTextElement("pageUrl","../c/" + node.pageUrl);
    }
    writer.writeEndElement();
}

void Generator::writeNodeListXml(QXmlStreamWriter &writer, QList<Node> &nodeList)
{
    writer.writeStartElement("nodeList");
    foreach(Node nodeItem, nodeList)
    {
        writeNodeXml(writer,nodeItem);
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
