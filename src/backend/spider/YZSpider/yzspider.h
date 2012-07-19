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
#include "core/xmlWriter/yzxmlwriter.h"
#include "yzspiderconfigfileparser.h"
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

    void ruleRequestReply();
private:
    //init
    void initParameters();

    //download
    void downloadWebPage(Node* node);
    void downloadRule(RuleRequest ruleRequest);

    //scheduler
    void webpageDownloadScheduler();
    void ruleRequestScheduler();

    //parse website data
    void parseWebsiteData();
    void parseNodeData(Node &nodeItem);
    void parseRuleData(Rule* ruleItem, Node &parentNode);
    void parseNodeListData(Rule* ruleItem);

    //parse rule reply
    void parseRuleReply(Rule* ruleItem,QByteArray& data, QUrl &baseUrl);
    void parseNextPage(RuleRequest ruleRequest);

    //output xml dir and download webpages
    void outputWebsite(QString fileName);
    QNetworkAccessManager *m_networkAccessManager;
    QMap<QNetworkReply*,Node*> m_webPageDownloadingTask;
    QLinkedList<Node*> m_webPageRequestTask;
    QMap<QNetworkReply*,RuleRequest> m_ruleDownloadingTask;
    QLinkedList<RuleRequest> m_ruleRequestTask;

    QSet<QString> m_nodeUrlSet;
    QSet<QString> m_resolvedNodes;

    int m_webpageRequestThreadNum;
    int m_ruleRequestThreadNum;
    quint32 m_webPageCount;
    WebSite m_website;
    bool m_finishParseRules;
    QUrl m_websiteUrl;
    YZSpiderConfigFileParser m_configFileParser;

    int m_maxWebPageRequestThreadNum;
    int m_maxRuleRequestThreadNum;

    QScriptEngine m_engine;
    QScriptValue m_globalValue;
    QScriptValue m_spiderValue;

    QMap<QString, QString> m_paramenters;
};

#endif // YZSPIDER_H
