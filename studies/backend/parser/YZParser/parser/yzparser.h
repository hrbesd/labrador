#ifndef YZPARSER_H
#define YZPARSER_H

#include <QObject>
#include <QFile>
#include "DataInterface.h"
#include "../xmlWriter/yzxmlwriter.h"

/*********************************************
 *          parser interface class
 *
 *
 *********************************************/
class YZParser : public QObject
{
    Q_OBJECT
public:
    explicit YZParser(QObject *parent = 0);
    //success return 0, else return -1
    virtual int parseFile(QString fileName) = 0;
signals:
    
public slots:
protected:
    ArticalInterface m_articalInterface;
};

#endif // YZPARSER_H
