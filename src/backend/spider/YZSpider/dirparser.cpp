#include "dirparser.h"
#include <QFile>
#include <QDir>

QString DirParser::workerDir = "";

DirParser::DirParser(QObject *parent) :
    QObject(parent)
{
}

void DirParser::parseDirFile(QString dirFile, WebSite &website)
{
    QFile file(dirFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("can't open dir File");
        exit(0);
    }
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name()=="codec")
            {
                website.codecName=xmlReader.readElementText();
            }
            else if(xmlReader.name()=="node")
            {
                parseNode(xmlReader,website);
            }
        }
        xmlReader.readNext();
    }
    file.close();
}

void DirParser::parseNode(QXmlStreamReader &reader, WebSite &website)
{
    reader.readNext();
    Node node;
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="node")
        {
            if(!checkWhetherNodeExists(node))
            {
                website.webPageRequestTask.append(node);
            }
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
            else if(reader.name()=="refreshRate")
            {
                node.refreshRate = reader.readElementText();
            }
            else if(reader.name()=="hashName")
            {
                node.hashName = reader.readElementText();
            }
            else if(reader.name()=="nodeList")
            {
                parseNodeList(reader,website);
            }
        }
        reader.readNext();
    }
}

void DirParser::parseNodeList(QXmlStreamReader &reader, WebSite &website)
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
                parseNode(reader,website);
            }
        }
        reader.readNext();
    }
}

bool DirParser::checkWhetherNodeExists(Node &nodeItem)
{
    QString fileName = nodeItem.hashName;
    QDir folderDir(DirParser::workerDir);
    QFile file(folderDir.absolutePath() + "/"+fileName.left(2)+"/"+ fileName);
    return file.exists();
}
