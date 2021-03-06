#ifndef FORERUNNER_H
#define FORERUNNER_H

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

class ForeRunner : public QObject
{
    Q_OBJECT
public:
    explicit ForeRunner(QObject *parent = 0);
signals:

protected slots:
    void networkError(QNetworkReply::NetworkError error);

    void ruleRequestReply();
private:
    //init
    void initParameters();

    //download
    void downloadRule(RuleRequest ruleRequest);

    //scheduler
    void ruleRequestScheduler();

    //parse website data
    void parseWebsiteData();
    void parseNodeData(Node &nodeItem);
    void parseRuleData(Rule* ruleItem, Node &parentNode);
    void parseNodeListData(Rule* ruleItem);

    //parse rule reply
    void parseRuleReply(Rule* ruleItem,QByteArray& data, QUrl &baseUrl);
    QStringList parseRuleExpression(Expression & expressionItem,const QString& strData);

    //output xml dir and download webpages
    void outputWebsite(QString fileName);

    void encodeURI(const QString& str, QByteArray &outArr);

    //tools
    bool checkWhetherNodeExists(Node &nodeItem);
    QNetworkAccessManager *m_networkAccessManager;
    QMap<QNetworkReply*,RuleRequest> m_ruleDownloadingTask;
    QLinkedList<RuleRequest> m_ruleRequestTask;

    QSet<QString> m_nodeUrlSet;
    QSet<QString> m_resolvedNodes;  //扫描过的url集合
    QSet<QString> m_resolvedRules;  // 扫描过的rule集合

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
    QTextCodec *codec;

    QMap<QString, QString> m_paramenters;
};

#endif // FORERUNNER_H
