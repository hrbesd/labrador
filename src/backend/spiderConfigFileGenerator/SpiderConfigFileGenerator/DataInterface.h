#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
struct Node;

struct Expression
{
    Expression(QString labelPara = "",QString valuePara = "") {
        type = "RegExp";
        executeOnlyOnce = "false";
        label =  labelPara;
        value = valuePara;
    }
    QString type;         //value type: {RegExp, JavaScript}
    QString executeOnlyOnce;     //execute only once flag : {true,false}
    QString label;     // used as key
    QString value;     // used as value
};

struct Rule
{
    Rule() {
        childRule=NULL;
        nextPageExpression.label = "nextPage";
    }
    QList<Expression> expressionList;
    Expression nextPageExpression;
    QString maxPageCount;
    QList<Node> nodeList;
    Rule* childRule;
};

struct Node
{
    QString url;
    QString name;
    QString refreshRate;
    QList<Rule*> ruleList;
};

struct WebSite
{
    Node node;
    QString info;
    QString editor;
    QString crawlTime;
    QString threadLimit;
};
#endif // DATAINTERFACE_H
