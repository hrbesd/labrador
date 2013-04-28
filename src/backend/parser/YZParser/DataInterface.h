#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>

struct HashNode
{
    QString absoluteUrl;
    QString originalUrl;
    QString hash;
};

/***********************************
 *  XML data structure
 *
 ***********************************/
struct ArticleInterface
{
//20130428
    QString ptitle;

    QString title;
    QString author;
    QString lastModified; //mseconds since Epoch
    QString bodyData;
    QString url;
    QList<HashNode> hashData;
};
#endif // DATAINTERFACE_H
