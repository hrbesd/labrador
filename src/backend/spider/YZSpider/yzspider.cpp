#include "yzspider.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
  ,m_maxWebPageRequestThreadNum(10)
  ,m_webPageCount(0)
{
    initParameters();
    m_networkAccessManager = new QNetworkAccessManager(this);
    DirParser::workerDir = m_paramenters.value("--worker-dir");
    DirParser::parseDirFile(m_paramenters.value("--dir-file"),website);
    //add updatelist.dat file
    //record what files should be updated

    QDir sharedDir(m_paramenters.value("--dir-file"));
    sharedDir.cdUp ();
    QFile updateFile(sharedDir.absolutePath ()+"/updatelist.dat");
    if (!updateFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&updateFile);
    QLinkedList<Node>::const_iterator i;
    for (i = website.webPageRequestTask.constBegin(); i != website.webPageRequestTask.constEnd(); ++i)
        out<<(*i).hashName<<"\n";
    updateFile.close ();

    if(website.codecName.isEmpty())
    {
        codec = QTextCodec::codecForName("utf8");
    }
    else
    {
        codec = QTextCodec::codecForName(website.codecName.toUtf8());
    }
    m_webpageRequestThreadNum = m_maxWebPageRequestThreadNum;
    webpageDownloadScheduler();
}

void YZSpider::downloadWebPage(Node &node)
{
    m_webpageRequestThreadNum--;
    QNetworkRequest request;
    QNetworkReply *reply;
    QByteArray encodedUrl;
    encodeURI(node.url, encodedUrl);
    QUrl requestUrl;
    requestUrl.setEncodedUrl (encodedUrl);
    request.setUrl(requestUrl);
    reply = m_networkAccessManager->get(request);
    m_webPageDownloadingTask.insert(reply,node);
    connect(reply,SIGNAL(finished()),this,SLOT(webPageDownloaded()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}


void YZSpider::webPageDownloaded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    Node nodeItem = m_webPageDownloadingTask.take(reply);
    QString fileName = nodeItem.hashName;
    QDir folderDir;
    folderDir.mkpath(m_paramenters.value("--worker-dir"));
    folderDir.cd(m_paramenters.value("--worker-dir"));
    folderDir.mkpath(folderDir.absolutePath() + "/"+fileName.left(2));
    QFile file(folderDir.absolutePath() + "/"+fileName.left(2)+"/"+ fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("can't save webpage");
        return;
    }
    file.write("\n");
    file.write(nodeItem.name.toUtf8().toBase64 ());
    file.write("\n");
    file.write(reply->url().toString().toUtf8().toBase64 ());
    file.write("\n");
    file.write(codec->toUnicode(result).toUtf8());
    qDebug()<<QString::number(m_webPageCount++)+ " web page downloaded";
    file.close();
    reply->deleteLater();
    m_webpageRequestThreadNum++;
    webpageDownloadScheduler();
}

void YZSpider::webpageDownloadScheduler()
{
    while(m_webpageRequestThreadNum>0&&website.webPageRequestTask.isEmpty()==false)
    {
        Node nodeItem = website.webPageRequestTask.takeFirst();
        downloadWebPage(nodeItem);
    }
    if(website.webPageRequestTask.isEmpty()&&m_webpageRequestThreadNum==m_maxWebPageRequestThreadNum)
    {
        qDebug()<<"finish download webpages";
        exit(0);
    }
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    YZLogger::Logger()->log(YZLogger::Error,reply->url().toString(),reply->errorString());
}

void YZSpider::initParameters()
{
    QStringList parametersList = QCoreApplication::arguments();
    foreach(QString parameter,parametersList)
    {
        QStringList tmpList = parameter.split('=');
        m_paramenters.insert(tmpList[0],tmpList.size()>1?tmpList[1]:QString(""));
    }

    if(m_paramenters.contains("--version"))
    {
        std::cout<<"Labrador Spider Version "<<BASE_VERSION<<endl;
        exit(0);
    }
    if(m_paramenters.contains("--log-file"))
    {
        YZLogger::logFilePath = m_paramenters.value("--log-file");
    }
    if(!m_paramenters.contains("--worker-dir"))
    {
        std::cerr<<"worker dir can't be empty, spider will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--dir-file"))
    {
        std::cerr<<"dir file can't be empty, spider will exit now!"<<endl;
        exit(0);
    }
    std::cout<<"spider start to run..."<<std::endl;
}

void YZSpider::encodeURI (const QString &str, QByteArray &outArr)
{
    QTextCodec *codec = QTextCodec::codecForName(website.codecName.toAscii ());
    if(codec->canEncode(str)) {
        QByteArray tmpArr;
        tmpArr = codec->fromUnicode(str);
        for(int i=0,size = tmpArr.length();i<size;i++){
            char ch = tmpArr.at(i);
            if(ch < 128 && ch > 0){
                outArr.append(ch);
            }else{
                uchar low = ch & 0xff;
                char c[3];
                sprintf(c,"%02X",low);
                outArr.append("%").append(c);
            }
        }
    }
}
