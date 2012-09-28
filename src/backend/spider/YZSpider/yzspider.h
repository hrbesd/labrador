#ifndef YZSPIDER_H
#define YZSPIDER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QCryptographicHash>
#include <QSet>
#include <QtScript>
#include "yzlogger.h"
#include <iostream>
#include <QUrl>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QLinkedList>
#include "DataInterface.h"
#include <QMap>
#include "version.h"
#include "dirparser.h"

using namespace std;
/**************************************************
 * download webpage in whitelist and convert text codec
 * to UTF-8
 *
 ************************************************/

class YZSpider : public QObject
{
    Q_OBJECT
public:
    explicit YZSpider(QObject *parent = 0);
signals:
    
protected slots:
    void webPageDownloaded();
    void networkError(QNetworkReply::NetworkError error);

private:
    //init
    void initParameters();

    //download
    void downloadWebPage(Node& node);

    //scheduler
    void webpageDownloadScheduler();

    //tools
    QNetworkAccessManager *m_networkAccessManager;
    QMap<QNetworkReply*,Node> m_webPageDownloadingTask;

    int m_webpageRequestThreadNum;
    int m_maxWebPageRequestThreadNum;
    quint32 m_webPageCount;

    QTextCodec *codec;
    WebSite website;

    QMap<QString, QString> m_paramenters;
};

#endif // YZSPIDER_H
