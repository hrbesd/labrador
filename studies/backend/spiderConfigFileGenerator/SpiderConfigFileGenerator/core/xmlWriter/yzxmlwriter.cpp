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
    writer.writeTextElement("websiteName", websiteItem.websiteName);
    writer.writeTextElement("regExp",websiteItem.regExp);
    writer.writeTextElement("url",websiteItem.url);

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
    writer.writeTextElement("url",nodeItem.url);
    writer.writeTextElement("regExp",nodeItem.regExp);
    writer.writeTextElement("nextPageRegExp",nodeItem.nextPageRegExp);
    writer.writeTextElement("maxPageCount",nodeItem.maxPageCount);
    writer.writeTextElement("refreshRate",nodeItem.refreshRate);
    writer.writeTextElement("titleRegExp",nodeItem.titleRegExp);
    writer.writeStartElement("NodeList");
    foreach(Node nodeItem, nodeItem.nodeList)
    {
        writeNodeItemToXml(nodeItem,writer);
    }
    writer.writeEndElement();
}
