#include "harbingovparser.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>

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
    QByteArray lastModifiedTime = file.readLine();
    QByteArray webData = file.readAll();

    QByteArray lastModified, author, title, body;

    lastModified = lastModifiedTime.trimmed();

    int startIndex = webData.lastIndexOf("detail_zw");
    startIndex = webData.indexOf("<P>",startIndex);
    int endIndex = webData.indexOf("</div>",startIndex);
    body = webData.mid(startIndex,endIndex - startIndex);
    int titleStartIndex = webData.indexOf("<P align=\"center\">",startIndex)+18;
    int titleEndIndex = webData.indexOf("</P>",titleStartIndex);
    title = webData.mid(titleStartIndex,titleEndIndex - titleStartIndex);
    int authorStartIndex = webData.indexOf("<P align=\"center\">",titleEndIndex)+18;
    int authorEndIndex = webData.indexOf("</P>",authorStartIndex);
    author = webData.mid(authorStartIndex,authorEndIndex - authorStartIndex);

    m_articleInterface.lastModified = QString::fromUtf8(lastModified.data());
    m_articleInterface.title = QString::fromUtf8(title.data());
    m_articleInterface.author = QString::fromUtf8(author.data());
    m_articleInterface.bodyData = QString::fromUtf8(body.data());
    QFileInfo fileInfo(file);
    QDir fileDir = fileInfo.absoluteDir();
    fileDir.cd("../result");
    YZXmlWriter::writeArticleToXml(m_articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName()+".xml");
    qDebug()<<"done";
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
