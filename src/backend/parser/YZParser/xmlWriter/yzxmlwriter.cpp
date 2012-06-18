#include "yzxmlwriter.h"
#include <QDebug>

YZXmlWriter::YZXmlWriter(QObject *parent) :
    QObject(parent)
{
}

void YZXmlWriter::writeArticleToXml(ArticleInterface &data, QString fileName)
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
    writer.writeStartElement("article");
    writer.writeTextElement("title", data.title);
    writer.writeTextElement("author",data.author);
    writer.writeTextElement("lastModified",data.lastModified);
    writer.writeTextElement("bodyData",data.bodyData);
    if(!data.hashData.isEmpty())
    {
        writer.writeStartElement("hashData");
        foreach(HashNode node, data.hashData)
        {
            writer.writeStartElement("hashNode");
            writer.writeTextElement("hash",node.hash);
            writer.writeTextElement("url",node.url);
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}
