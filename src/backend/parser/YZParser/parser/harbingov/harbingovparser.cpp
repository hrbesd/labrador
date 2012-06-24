//#include "harbingovparser.h"
//#include <QDebug>
//#include <QCoreApplication>
//#include <QFileInfo>
//#include <QCryptographicHash>

//HarbinGovParser::HarbinGovParser(QObject *parent) :
//    YZParser(parent)
//{
//    QDir dir("webpage/spider");
//    if(!dir.exists())
//    {
//        qWarning()<<"can't find parse folder";
//        return;
//    }
//    dir.mkpath("../parser");
//    parseFolder("webpage/spider");
//}

//int HarbinGovParser::parseFile(QString fileName)
//{
//    QFile file(fileName);
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qWarning()<<"can't open parse file";
//        return -1;
//    }
//    ArticleInterface articleInterface;
//    QByteArray lastModifiedTime = file.readLine();
//    QByteArray title = file.readLine();
//    QByteArray baseUrl = file.readLine();
//    QByteArray webData = file.readAll();

//    QByteArray lastModified, author, body;

//    lastModified = lastModifiedTime.trimmed();

//    int startIndex = webData.lastIndexOf("detail_zw");
//    startIndex = webData.indexOf("<div",startIndex);
//    int endIndex = webData.indexOf("</div>",startIndex)+6;
//    body = webData.mid(startIndex,endIndex - startIndex);
//    if(body=="<!DOC")
//    {
//        startIndex = webData.lastIndexOf("<div id=\"zoom\" class=\"detail_zw\" align=\"left\">");
//        endIndex = webData.indexOf("</div>",startIndex)+6;
//        body = webData.mid(startIndex,endIndex - startIndex);
//    }
//    int authorStartIndex = webData.lastIndexOf("detail_ly");
//    if(authorStartIndex!=-1)
//    {
//        authorStartIndex = webData.indexOf(">",authorStartIndex)+1;
//        int authorEndIndex = webData.indexOf("<",authorStartIndex);
//        author = webData.mid(authorStartIndex,authorEndIndex - authorStartIndex);
//    }
//    articleInterface.lastModified = QString::fromUtf8(lastModified.data());
//    articleInterface.title = QString::fromUtf8(title.data());
//    articleInterface.author = QString::fromUtf8(author.data());
//    articleInterface.bodyData = QString::fromUtf8(body.data());
//    articleInterface.url = QString::fromUtf8((baseUrl.data()));

//    parseImageFromBody(articleInterface.bodyData,QString(baseUrl),articleInterface);
//    QFileInfo fileInfo(file);
//    QDir fileDir = fileInfo.absoluteDir();
//    QString newPath = fileDir.absolutePath().replace("/spider/","/parser/");
//    fileDir.mkpath(newPath);
//    fileDir.cd(newPath);
//    YZXmlWriter::writeArticleToXml(articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName()+".xml");
//    static int webpageCount = 0;
//    qDebug()<<(webpageCount++)<<" done";
//    file.close();
//    return 0;
//}

//void HarbinGovParser::parseFolder(QString folder)
//{
//    QDir dir(folder);
//    if(!dir.exists())
//    {
//        qWarning()<<"can't find parse folder";
//        return;
//    }

//    QFileInfoList fileInfolists= dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
//    foreach(QFileInfo fileInfo, fileInfolists)
//    {
//        if(fileInfo.isFile())
//        {
//            parseFile(fileInfo.absoluteFilePath());
//        }
//        else
//        {
//            parseFolder(fileInfo.absoluteFilePath());
//        }
//    }
//    qDebug()<<"finish";

//}

//void HarbinGovParser::parseImageFromBody(const QString &dataString, QString base, ArticleInterface &articleInterface)
//{
//    int index=-1;
//    while(1)
//    {
//        index = dataString.indexOf("<img",index+1,Qt::CaseInsensitive);
//        if(index==-1)
//        {
//            return;
//        }
//        int urlStartIndex = dataString.indexOf("src=",index,Qt::CaseInsensitive)+5;
//        int urlEndIndex = dataString.indexOf("\"",urlStartIndex);

//        QUrl baseUrl(base);
//        QUrl subUrl(QString(dataString.mid(urlStartIndex,urlEndIndex - urlStartIndex)));
//        QUrl url ;
//        if(subUrl.isRelative())
//        {
//            url = baseUrl.resolved(subUrl);
//        }
//        else
//        {
//            url = subUrl;
//        }
//        HashNode node;
//        node.absoluteUrl = url.toString();
//        node.originalUrl = subUrl.toString();
//        node.hash = QCryptographicHash::hash(url.toString().toUtf8(),QCryptographicHash::Md5).toHex();
//        articleInterface.hashData.append(node);
//    }
//}
