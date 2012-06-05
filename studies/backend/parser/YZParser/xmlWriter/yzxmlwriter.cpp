#include "yzxmlwriter.h"
#include <QDebug>

YZXmlWriter::YZXmlWriter(QObject *parent) :
    QObject(parent)
{
}

void YZXmlWriter::writeArticalToXml(ArticalInterface &data, QString fileName)
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
    writer.writeStartElement("artical");
    writer.writeTextElement("title", data.title);
    writer.writeTextElement("author",data.author);
    writer.writeTextElement("lastModified",data.lastModified);
    writer.writeTextElement("bodyData",data.bodyData);
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}
