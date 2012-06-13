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
    QString url;
    QString urlRegExp;
    QString nameRegExp;
    QString name;
    QList<Node> nodeList;
};
#endif // DATAINTERFACE_H
