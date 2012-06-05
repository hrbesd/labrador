#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>

/***********************************
 *  XML data structure
 *
 ***********************************/
struct ArticalInterface
{
    QString title;
    QString author;
    QString lastModified; //mseconds since Epoch
    QString bodyData;
};
#endif // DATAINTERFACE_H
