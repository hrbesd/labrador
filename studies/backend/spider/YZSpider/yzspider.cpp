#include "yzspider.h"
#include <QDebug>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

YZSpider::YZSpider(QString whiteListFileName, QObject *parent)
{
    m_networkAccessManager = new QNetworkAccessManager(this);
}

void YZSpider::downloadWebPage(QString url)
{
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(url));
    reply = m_networkAccessManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(webPageDownloaded()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::webPageDownloaded()
{
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
    file.write(result);
    qDebug()<<"done";
    file.close();
    reply->deleteLater();
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    qDebug()<<"error:"+error;
}
