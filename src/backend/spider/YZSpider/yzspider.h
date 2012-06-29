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
#include "yzlogger.h"
#include <QUrl>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QLinkedList>
#include "DataInterface.h"
#include <QMap>
#include "core/xmlWriter/yzxmlwriter.h"
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
    void parseWebsiteConfigFile(QString configFile);
signals:
    
protected slots:
    void webPageDownloaded();
    void networkError(QNetworkReply::NetworkError error);

    void ruleRequestReply();
private:
    //download
    void downloadWebPage(Node* node);
    void downloadRule(RuleRequest ruleRequest);

    //scheduler
    void webpageDownloadScheduler();
    void ruleRequestScheduler();
    //read xml file
    void parseWebsiteXml(QXmlStreamReader &reader);
    void parseNodeXml(QXmlStreamReader &reader, Node &node);
    void parseNodeListXml(QXmlStreamReader &reader, QList<Node>& parentNodeList);
    void parseRuleListXml(QXmlStreamReader &reader, QList<Rule*>& parentRuleList);
    void parseRuleXml(QXmlStreamReader &reader, Rule *rule);
    void parseChildRuleXml(QXmlStreamReader &reader, Rule *rule);
    void parseExpressionListXml(QXmlStreamReader &reader, Rule *rule);
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

    QXmlStreamReader xmlReader;

    static const int m_maxWebPageRequestThreadNum = 10;
    static const int m_maxRuleRequestThreadNum = 10;
};

#endif // YZSPIDER_H
