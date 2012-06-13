#include "yzxmlwriter.h"
#include <QDebug>

YZXmlWriter::YZXmlWriter(QObject *parent) :
    QObject(parent)
{
}

void YZXmlWriter::writeWebsiteItemToXml(WebSite &websiteItem, QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning()<<"can't open xml file";
        return;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("website");
    writer.writeTextElement("name", websiteItem.name);
    writer.writeTextElement("urlRegExp",websiteItem.urlRegExp);
    writer.writeTextElement("url",websiteItem.url);
    writer.writeTextElement("nameRegExp",websiteItem.nameRegExp);
    writer.writeStartElement("NodeList");
    foreach(Node nodeItem, websiteItem.nodeList)
    {
        writeNodeItemToXml(nodeItem,writer);
    }
    writer.writeEndElement();

    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void YZXmlWriter::writeNodeItemToXml(Node &nodeItem, QXmlStreamWriter &writer)
{
    writer.writeTextElement("name",nodeItem.name);
    writer.writeTextElement("url",nodeItem.url);
    writer.writeTextElement("urlRegExp",nodeItem.urlRegExp);
    writer.writeTextElement("nextPageRegExp",nodeItem.nextPageRegExp);
    writer.writeTextElement("maxPageCount",nodeItem.maxPageCount);
    writer.writeTextElement("refreshRate",nodeItem.refreshRate);
    writer.writeTextElement("nameRegExp",nodeItem.nameRegExp);
    writer.writeStartElement("NodeList");
    foreach(Node nodeItem, nodeItem.nodeList)
    {
        writeNodeItemToXml(nodeItem,writer);
    }
    writer.writeEndElement();
}
