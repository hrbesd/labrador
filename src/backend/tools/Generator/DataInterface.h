#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
struct Node
{
    Node(){ parentNode=NULL; }
    QString url;
    QString name;
    QString hashName;
    QString level;
    mutable QString pageUrl;
    Node* parentNode;
    QList<Node> nodeList;
};

struct WebSite
{
    QString info;
    QString name;
    QString url;
    Node node;
};

enum NodeType
{
    ColumnNode,
    ListNode,
    ArticleNode
};

#endif // DATAINTERFACE_H
