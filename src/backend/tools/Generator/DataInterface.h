#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
struct Node
{
    QString url;
    QString name;
    QString hashName;
    QList<Node> nodeList;
};

struct WebSite
{
    QString info;
    QString editor;
    Node node;
};

enum NodeType
{
    ColumnNode,
    ListNode,
    ArticleNode
};

#endif // DATAINTERFACE_H
