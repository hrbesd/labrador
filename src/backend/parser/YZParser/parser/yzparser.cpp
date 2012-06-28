#include "yzparser.h"

YZParser::YZParser(QObject *parent) :
    QObject(parent)
{
    QString fileName = "test.js";
    QFile scriptFile(fileName);
    if (!scriptFile.open(QIODevice::ReadOnly))
    {
    }
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();
    m_engine.evaluate(contents);
    m_globalValue = m_engine.globalObject();
    m_parserValue = m_globalValue.property("parseArticle");
    QDir dir("webpage/spider");
    if(!dir.exists())
    {
        qWarning()<<"can't find parse folder";
        return;
    }
    dir.mkpath("../parser");
    parseFolder("webpage/spider");
}

int YZParser::parseFile(QString fileName)
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

    QScriptValueList args;
    args << QScriptValue(webData.data());
    QScriptValue article = m_parserValue.call(QScriptValue(),args);
    QVariant articleItem = article.toVariant();

    articleInterface.lastModified = QString::fromUtf8(lastModifiedTime.trimmed().data());
    articleInterface.title = QString::fromUtf8(title.data());
    articleInterface.author = QString::fromUtf8(articleItem.toMap()["author"].toByteArray().data());
    articleInterface.bodyData = QString::fromUtf8(articleItem.toMap()["body"].toByteArray().data());
    articleInterface.url = QString::fromUtf8((baseUrl.data()));

    parseImageFromBody(articleInterface.bodyData,QString(baseUrl),articleInterface);
    QFileInfo fileInfo(file);
    QDir fileDir = fileInfo.absoluteDir();
    QString newPath = fileDir.absolutePath().replace("/spider/","/parser/");
    fileDir.mkpath(newPath);
    fileDir.cd(newPath);
    YZXmlWriter::writeArticleToXml(articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName()+".xml");
    static int webpageCount = 0;
    qDebug()<<(webpageCount++)<<" done";
    file.close();
    return 0;
}

void YZParser::parseFolder(QString folder)
{
    QDir dir(folder);
    if(!dir.exists())
    {
        qWarning()<<"can't find parse folder";
        return;
    }

    QFileInfoList fileInfolists= dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo fileInfo, fileInfolists)
    {
        if(fileInfo.isFile())
        {
            parseFile(fileInfo.absoluteFilePath());
        }
        else
        {
            parseFolder(fileInfo.absoluteFilePath());
        }
    }
    qDebug()<<"finish";

}

void YZParser::parseImageFromBody(const QString &dataString, QString base, ArticleInterface &articleInterface)
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
        node.absoluteUrl = url.toString();
        node.originalUrl = subUrl.toString();
        node.hash = QCryptographicHash::hash(url.toString().toUtf8(),QCryptographicHash::Md5).toHex();
        articleInterface.hashData.append(node);
    }
}
