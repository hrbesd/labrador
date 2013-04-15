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
    writer.writeTextElement("url", data.url);
    writer.writeTextElement("author",data.author);
    writer.writeTextElement("lastModified",data.lastModified);
    
  //20130415
  if(data.bodyData.length()<2)
  data.bodyData=data.bodyData+"<a  href="+data.url+">&#20869;&#23481;&#20026;&#31354;&#25110;&#21547;&#26080;&#27861;&#36716;&#25442;&#30340;&#35270;&#39057;&#12289;&#112;&#100;&#102;&#65292;&#35831;&#28857;&#20987;&#21407;&#22987;&#32593;&#39029;&#26597;&#30475;</a>";
    
    writer.writeTextElement("bodyData",data.bodyData);
    if(!data.hashData.isEmpty())
    {
        writer.writeStartElement("hashData");
        foreach(HashNode node, data.hashData)
        {
            writer.writeStartElement("hashNode");
            writer.writeTextElement("hash",node.hash);
            writer.writeTextElement("absoluteUrl",node.absoluteUrl);
            writer.writeTextElement("originalUrl",node.originalUrl);
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}
