#include "harbingovparser.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>
#include <QCryptographicHash>

HarbinGovParser::HarbinGovParser(QObject *parent) :
    YZParser(parent)
{
    parseFolder("webpage/original");
}

int HarbinGovParser::parseFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning()<<"can't open parse file";
        return -1;
    }
    ArticleInterface articleInterface;
    QByteArray lastModifiedTime = file.readLine();
    QByteArray title = file.readLine();
    QByteArray baseUrl = file.readLine();
    QByteArray webData = file.readAll();

    QByteArray lastModified, author, body;

    lastModified = lastModifiedTime.trimmed();

    int startIndex = webData.lastIndexOf("detail_zw");
    startIndex = webData.indexOf("<div",startIndex);
    int endIndex = webData.indexOf("</div>",startIndex)+6;
    body = webData.mid(startIndex,endIndex - startIndex);
    int authorStartIndex = webData.lastIndexOf("detail_ly");
    if(authorStartIndex!=-1)
    {
        authorStartIndex = webData.indexOf(">",authorStartIndex)+1;
        int authorEndIndex = webData.indexOf("<",authorStartIndex);
        author = webData.mid(authorStartIndex,authorEndIndex - authorStartIndex);
    }
    articleInterface.lastModified = QString::fromUtf8(lastModified.data());
    articleInterface.title = QString::fromUtf8(title.data());
    articleInterface.author = QString::fromUtf8(author.data());
    articleInterface.bodyData = QString::fromUtf8(body.data());

    parseImageFromBody(articleInterface.bodyData,QString(baseUrl),articleInterface);
    cleanBodyData(articleInterface.bodyData);
    QFileInfo fileInfo(file);
    QDir fileDir = fileInfo.absoluteDir();
    fileDir.cd("../result");
    YZXmlWriter::writeArticleToXml(articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName()+".xml");
    qDebug()<<"done";
    file.close();
    return 0;
}

void HarbinGovParser::parseFolder(QString folder)
{
    QDir dir(folder);
    if(!dir.exists())
    {
        qWarning()<<"can't find parse folder";
        return;
    }
    dir.mkpath("../result");

    QFileInfoList fileInfolists= dir.entryInfoList(QDir::Files);
    foreach(QFileInfo fileInfo, fileInfolists)
        parseFile(fileInfo.absoluteFilePath());
    qDebug()<<"finish";

}

void HarbinGovParser::parseImageFromBody(const QString &dataString, QString base, ArticleInterface &articleInterface)
{
    int index=-1;
    while(1)
    {
        index = dataString.indexOf("<img",index+1,Qt::CaseInsensitive);
        if(index==-1)
        {
            return;
        }
        int urlStartIndex = dataString.indexOf("src=",index,Qt::CaseInsensitive)+5;
        int urlEndIndex = dataString.indexOf("\"",urlStartIndex);

        QUrl baseUrl(base);
        QUrl subUrl(QString(dataString.mid(urlStartIndex,urlEndIndex - urlStartIndex)));
        QUrl url ;
        if(subUrl.isRelative())
        {
            url = baseUrl.resolved(subUrl);
        }
        else
        {
            url = subUrl;
        }
        HashNode node;
        node.url = url.toString();
        node.hash = QCryptographicHash::hash(url.toString().toUtf8(),QCryptographicHash::Md5).toHex();
        articleInterface.hashData.append(node);
    }
}

void HarbinGovParser::cleanBodyData(QString &bodyData)
{
    QList<QString> tagList;
    tagList<<QString("div");
    tagList<<QString("font");
    tagList<<QString("br");
    removeTags(bodyData,tagList);
    removeBlankCharacter(bodyData);
}

void HarbinGovParser::removeTags(QString &bodyData, QList<QString> tagList)
{
    foreach(QString tag, tagList)
    {
        removeTag(bodyData,tag);
    }
}

void HarbinGovParser::removeTag(QString &bodyData, QString tag)
{
    QRegExp startRx("<"+tag+"[^>]*>",Qt::CaseInsensitive);
    QRegExp endRx("</"+tag+">",Qt::CaseInsensitive);
    bodyData.replace(startRx,"");
    bodyData.replace(endRx,"");

}

void HarbinGovParser::removeBlankCharacter(QString &bodyData)
{

}
