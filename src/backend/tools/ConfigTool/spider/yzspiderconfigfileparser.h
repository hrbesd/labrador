#ifndef YZSPIDERCONFIGFILEPARSER_H
#define YZSPIDERCONFIGFILEPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDir>
#include <QFile>
#include <iostream>
#include "DataInterface.h"

class YZSpiderConfigFileParser : public QObject
{
    Q_OBJECT
public:
    explicit YZSpiderConfigFileParser(QObject *parent = 0);
    void parseWebsiteConfigFile(QString fileName,WebSite& m_website);
signals:

public slots:
private:
    //read xml file
    void parseWebsiteXml(QXmlStreamReader &reader,WebSite& m_website);
    void parseNodeXml(QXmlStreamReader &reader, Node *node);
    void parseNodeListXml(QXmlStreamReader &reader, QList<Node*>& parentNodeList);
    void parseRuleListXml(QXmlStreamReader &reader, QList<Rule*>& parentRuleList);
    void parseRuleXml(QXmlStreamReader &reader, Rule *rule);
    void parseChildRuleXml(QXmlStreamReader &reader, Rule *rule);
    void parseExpressionListXml(QXmlStreamReader &reader, Rule *rule);

};

#endif // YZSPIDERCONFIGFILEPARSER_H
