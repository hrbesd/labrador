#ifndef YZSPIDER_H
#define YZSPIDER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QCryptographicHash>
#include <QDateTime>

class YZSpider : public QObject
{
    Q_OBJECT
public:
    explicit YZSpider(QObject *parent = 0);
    YZSpider(QString whiteListFileName, QObject *parent = 0);
    void downloadWebPage(QString url);
signals:
    
protected slots:
    void webPageDownloaded();
    void networkError(QNetworkReply::NetworkError error);
private:
    QNetworkAccessManager *m_networkAccessManager;
};

#endif // YZSPIDER_H
