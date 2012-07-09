#include "yzparser.h"
#include <QCoreApplication>

YZParser::YZParser(QObject *parent) :
    QObject(parent)
{
    QStringList parametersList = QCoreApplication::arguments();
    foreach(QString parameter,parametersList)
    {
        QStringList tmpList = parameter.split('=');
        m_paramenters.insert(tmpList[0],tmpList.size()>1?tmpList[1]:QString(""));
    }

    if(m_paramenters.contains("--version"))
    {
        std::cout<<"Labrador Parser Version "<<BASE_VERSION<<endl;
    }
    if(m_paramenters.contains("--log-file"))
    {
        YZLogger::logFilePath = m_paramenters.value("--log-file");
    }
    if(!m_paramenters.contains("--rule-dir"))
    {
        std::cerr<<"rule dir can't be empty, parser will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--worker-dir"))
    {
        std::cerr<<"worker dir can't be empty, parser will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--shared-dir"))
    {
        std::cerr<<"shared dir can't be empty, parser will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--source-dir"))
    {
        std::cerr<<"source dir can't be empty, parser will exit now!"<<endl;
        exit(0);
    }
    QDir dir(m_paramenters.value("--rule-dir"));
    QString fileName = dir.absolutePath()+"/"+"parser_config.js";
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
    QDir sourceDir(m_paramenters.value("--source-dir"));
    if(!sourceDir.exists())
    {
        qWarning()<<"can't open parse source folder";
        exit(0);
    }
    parseFolder(m_paramenters.value("--source-dir"));
    qApp->exit(0);
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
    QDir fileDir;
    fileDir.mkpath(m_paramenters.value("--worker-dir"));
    fileDir.cd(m_paramenters.value("--worker-dir"));
    fileDir.mkpath(fileDir.absolutePath() + "/"+fileInfo.baseName().left(2));
    YZXmlWriter::writeArticleToXml(articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName().left(2)+"/"+fileInfo.baseName()+".xml");
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

void YZParser::parseConfigFile(QString parserConfigFileUrl)
{

}
