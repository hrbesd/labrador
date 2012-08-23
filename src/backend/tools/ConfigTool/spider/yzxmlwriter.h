#ifndef YZXMLWRITER_H
#define YZXMLWRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QtXml/QXmlStreamWriter>
#include <QtXml/QDomElement>
#include "../DataInterface.h"

/***********************************************
 *          XML Writer
 *
 **********************************************/
class YZXmlWriter : public QObject
{
    Q_OBJECT
public:
    explicit YZXmlWriter(QObject *parent = 0);
    static void writeWebsiteItemToXml(WebSite &websiteItem, QString fileName);
private:
    static void writeNodeItemToXml(const Node *nodeItem, QXmlStreamWriter& writer);
    static void writeRuleItemToXml(const Rule *ruleItem, QXmlStreamWriter& writer);
    static void writeExpressionItemToXml(const Expression& expressionItem, QXmlStreamWriter& writer);
signals:

public slots:

};

#endif // YZXMLWRITER_H
