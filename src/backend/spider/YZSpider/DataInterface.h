#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QLinkedList>

struct Node
{
    QString url;
    QString name;
    QString hashName;
    QString refreshRate;
};

struct WebSite
{
    QLinkedList<Node> webPageRequestTask;
    QString crawlTime;
    QString threadLimit;
    QString codecName;
};

#endif // DATAINTERFACE_H
