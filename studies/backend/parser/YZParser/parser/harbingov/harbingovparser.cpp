#include "harbingovparser.h"
#include <QDebug>

HarbinGovParser::HarbinGovParser(QObject *parent) :
    YZParser(parent)
{
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

    m_articalInterface.lastModified = QString::fromUtf8(lastModified.data());
    m_articalInterface.title = QString::fromUtf8(title.data());
    m_articalInterface.author = QString::fromUtf8(author.data());
    m_articalInterface.bodyData = QString::fromUtf8(body.data());
    YZXmlWriter::writeArticalToXml(m_articalInterface,fileName+".xml");
    qDebug()<<"finish";
    return 0;
}
