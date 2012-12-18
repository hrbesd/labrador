#include "yzparser.h"
#include <QTime>
#include <QCoreApplication>

YZParser::YZParser(QObject *parent) :
    QObject(parent),m_webpageCount(0)
{
    initParameters();
    QDir dir(m_paramenters.value("--rule-dir"));
    QString fileName = dir.absolutePath()+"/"+"parser_config.js";
    QFile scriptFile(fileName);
    if (!scriptFile.open(QIODevice::ReadOnly))
    {
        std::cerr<<"can't open parser config file, exit now!"<<std::endl;
        exit(0);
    }
    std::cout<<"parser start to run..."<<std::endl;
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

    QTime time;
    time.start();
    parseFolder(m_paramenters.value("--source-dir"));
    qDebug()<<"finish";
    qDebug()<<time.elapsed()<<":"<<m_webpageCount;
    exit(0);
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
    file.readLine();
    QByteArray title = file.readLine();
    QByteArray baseUrl = file.readLine();
    QByteArray webData = file.readAll();

    QScriptValueList args;
    args << QScriptValue(webData.data())<<QScriptValue(baseUrl.data());
    QScriptValue article = m_parserValue.call(QScriptValue(),args);
    QVariant articleItem = article.toVariant();

    QString configFileVersion = QString::fromUtf8(articleItem.toMap()["version"].toByteArray().data());
    if(configFileVersion.compare(QString(BASE_VERSION))!=0)
    {
        std::cerr<<"config file version is:"<<configFileVersion.toStdString()<<std::endl;
        std::cerr<<"parser version is:"<<BASE_VERSION<<std::endl;
        std::cerr<<"parser don't support this version of config file, will exit now!"<<std::endl;
        exit(0);
    }

    articleInterface.lastModified = QString::fromUtf8(articleItem.toMap()["lastModified"].toByteArray().data());
    articleInterface.title = QString::fromUtf8(title.data());
    articleInterface.author = QString::fromUtf8(articleItem.toMap()["author"].toByteArray().data());
    articleInterface.bodyData = QString::fromUtf8(articleItem.toMap()["body"].toByteArray().data());
    cleanBodyData(articleInterface.bodyData);
    articleInterface.url = QString::fromUtf8((baseUrl.data()));
    if(articleItem.toMap()["refreshTag"].toByteArray().data()=="true")
    {
        YZLogger::Logger()->log(YZLogger::Warning,articleInterface.url,"contains: http-equiv=\"refresh\"");
    }
    removeStyles(articleInterface.bodyData);
    parseImageFromBody(articleInterface.bodyData,QString(baseUrl),articleInterface);
    QFileInfo fileInfo(file);
    QDir fileDir;
    fileDir.mkpath(m_paramenters.value("--worker-dir"));
    fileDir.cd(m_paramenters.value("--worker-dir"));
    fileDir.mkpath(fileDir.absolutePath() + "/"+fileInfo.baseName().left(2));
    YZXmlWriter::writeArticleToXml(articleInterface,fileDir.absolutePath()+"/"+fileInfo.baseName().left(2)+"/"+fileInfo.baseName()+".xml");
    m_webpageCount++;
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

void YZParser::initParameters()
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
        exit(0);
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
}

void YZParser::removeStyles(QString &data)
{
    QRegExp regExp("style=\"[^\"]*\"");
    regExp.setMinimal(true);
    data.replace(regExp,"");
}

void YZParser::cleanBodyData(QString &bodyData)
{
    QList<QString> tagList;
    tagList<<QString("font");
    removeTags(bodyData,tagList);
}

void YZParser::removeTags(QString &bodyData, QList<QString> tagList)
{
    foreach(QString tag, tagList)
    {
        removeTag(bodyData,tag);
    }
}

void YZParser::removeTag(QString &bodyData, QString tag)
{
    QRegExp startRx("<"+tag+"[^>]*>",Qt::CaseInsensitive);
    QRegExp endRx("</"+tag+">",Qt::CaseInsensitive);
    bodyData.replace(startRx,"");
    bodyData.replace(endRx,"");

}
