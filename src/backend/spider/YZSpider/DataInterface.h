#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>

struct Node;
struct Rule;
struct RuleRequest
{
    Rule* rule;
    QString url;
};

struct Expression
{
    void copyFromExpression(const Expression& otherExpression)
    {
        this->type = otherExpression.type;
        this->label = otherExpression.label;
        this->value = otherExpression.value;
        this->executeOnlyOnce = otherExpression.executeOnlyOnce;
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
    }
    QList<Expression> expressionList;
    Expression nextPageExpression;
    Expression urlExpression;
    Expression titleExpression;
    QString maxPageCount;
    QList<Node> nodeList;
    Rule* childRule;
};

struct Node
{
    QString url;
    QString name;
    QString hashName;
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
    QString codecName;
};

#endif // DATAINTERFACE_H
