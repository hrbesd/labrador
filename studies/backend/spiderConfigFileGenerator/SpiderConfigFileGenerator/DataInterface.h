#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>

struct Node
{
    QString url;
    QString regExp;
    QString nextPageRegExp;
    QString maxPageCount;
    QString refreshRate;
    QString titleRegExp;
    QList<Node> nodeList;
};

struct WebSite
{
    QString url;
    QString regExp;
    QString websiteName;
    QList<Node> nodeList;
};
#endif // DATAINTERFACE_H
