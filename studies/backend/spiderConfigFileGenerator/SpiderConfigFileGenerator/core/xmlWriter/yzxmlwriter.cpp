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
    writer.writeTextElement("editor", websiteItem.editor);
    writer.writeTextElement("info",websiteItem.info);
    YZXmlWriter::writeNodeItemToXml(websiteItem.node,writer);

    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void YZXmlWriter::writeNodeItemToXml(Node &nodeItem, QXmlStreamWriter &writer)
{
    writer.writeStartElement("node");
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
    writer.writeEndElement();
}
