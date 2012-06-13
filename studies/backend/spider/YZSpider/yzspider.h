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
#include <QUrl>
#include <QDateTime>
#include <QMap>
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
    YZSpider(QString whiteListFileName, QObject *parent = 0);
    void downloadWebPage(QString url);
    void parseLinks(QString url);
    void parseConfigFile(QString configFile);
signals:
    
protected slots:
    void webPageDownloaded();
    void parseLinksReply();
    void networkError(QNetworkReply::NetworkError error);
private:
    void downloadScheduler();
    QString getSubUrl(QByteArray &data, int index);
    QByteArray getTitle(QByteArray &data, int index);
    QNetworkAccessManager *m_networkAccessManager;
    QSet<QString> m_innerLinks; //站内链接
    QSet<QString> m_outerLinks; //站外链接
    QMap<QString, QByteArray> m_titleLinkMap;

    int m_threadLimit;
    quint32 m_webPageCount;
};

#endif // YZSPIDER_H
