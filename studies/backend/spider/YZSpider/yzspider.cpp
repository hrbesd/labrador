#include "yzspider.h"
#include <QDebug>
#include <QTextCodec>
#include <QTextDecoder>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
{
    m_threadLimit = 10;
    m_networkAccessManager = new QNetworkAccessManager(this);
}

YZSpider::YZSpider(QString whiteListFileName, QObject *parent)
{
    m_threadLimit = 10;
    m_networkAccessManager = new QNetworkAccessManager(this);
}

void YZSpider::downloadWebPage(QString url)
{
    m_threadLimit--;
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(url));
    reply = m_networkAccessManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(webPageDownloaded()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::webPageDownloaded()
{
    m_threadLimit++;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QString fileName = QCryptographicHash::hash(QByteArray(reply->url().toString().toUtf8()),QCryptographicHash::Md5).toHex();
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("can't save webpage");
        return;
    }
    file.write((QString::number(reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toMSecsSinceEpoch())+"\n").toAscii());
    file.write(QTextCodec::codecForHtml(result)->toUnicode(m_titleLinkMap.value(reply->url().toString())).toUtf8());
    file.write("\n");
    file.write(QTextCodec::codecForHtml(result)->toUnicode(result).toUtf8());
    qDebug()<<"done";
    file.close();
    reply->deleteLater();
    downloadScheduler();
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    qDebug()<<"error:"+error;
}

void YZSpider::parseLinks(QString url)
{
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(url));
    reply = m_networkAccessManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(parseLinksReply()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::parseLinksReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QUrl baseUrl = reply->url();
    int index = -1;
    while(1)
    {
        index = result.indexOf("<a class=\"f3348\"",index+1);
        if(index==-1)
        {
            break;
        }
        QUrl subUrl = getSubUrl(result,index);
        QByteArray title = getTitle(result,index);
        if(subUrl.isRelative())
        {
            m_innerLinks.insert(baseUrl.resolved(subUrl).toString());
            m_titleLinkMap.insert(baseUrl.resolved(subUrl).toString(),title);
        }
        else
        {
            m_outerLinks.insert(subUrl.toString());
            m_titleLinkMap.insert(subUrl.toString(),title);
        }
    }

    index = result.indexOf("class=\"Next\">");
    if(index==-1)
    {
        downloadScheduler();
    }
    else
    {
        index = result.lastIndexOf("<a",index);
        parseLinks(baseUrl.resolved(QUrl(getSubUrl(result,index))).toString());
    }

    reply->deleteLater();
}

QString YZSpider::getSubUrl(QByteArray &data, int index)
{
    int startIndex = data.indexOf("href=",index)+6;
    int endIndex = data.indexOf("\"",startIndex);
    return QString(data.mid(startIndex,endIndex - startIndex));
}

QByteArray YZSpider::getTitle(QByteArray &data, int index)
{
    int startIndex = data.indexOf("title=",index)+7;
    int endIndex = data.indexOf("\"",startIndex);
    return data.mid(startIndex,endIndex - startIndex);
}

void YZSpider::downloadScheduler()
{
    while(m_threadLimit>=0&&m_innerLinks.isEmpty()==false)
    {
        QString url = *(m_innerLinks.begin());
        m_innerLinks.erase(m_innerLinks.begin());
        downloadWebPage(url);
    }
    if(m_innerLinks.isEmpty()&&m_threadLimit==10)
    {
        qDebug()<<"finish";
    }
}