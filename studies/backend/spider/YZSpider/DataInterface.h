#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>

struct Node
{
    QString url;
    QString name;
    QString urlRegExp;
    QString nextPageRegExp;
    QString maxPageCount;
    QString refreshRate;
    QString nameRegExp;
    QList<Node> nodeList;
};

struct WebSite
{
    Node node;
    QString info;
    QString editor;
};

#endif // DATAINTERFACE_H
