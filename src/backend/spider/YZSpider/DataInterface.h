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

struct Rule
{
    Rule() { childRule=NULL; }
    QString urlRegExp;
    QString nextPageRegExp;
    QString maxPageCount;
    QString nameRegExp;
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
};

#endif // DATAINTERFACE_H