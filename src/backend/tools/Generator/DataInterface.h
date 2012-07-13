#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
struct Node
{
    QString url;
    QString name;
    QString pageUrl;
    QList<Node> nodeList;
};



struct WebSite
{
    QString info;
    QString editor;
    Node node;
};

#endif // DATAINTERFACE_H
