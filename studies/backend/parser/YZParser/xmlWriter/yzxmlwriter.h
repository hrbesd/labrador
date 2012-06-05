#ifndef YZXMLWRITER_H
#define YZXMLWRITER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QtXml/QXmlStreamWriter>
#include <QtXml/QDomElement>
#include "../DataInterface.h"

/***********************************************
 *          XML Writer
 *
 **********************************************/
class YZXmlWriter : public QObject
{
    Q_OBJECT
public:
    explicit YZXmlWriter(QObject *parent = 0);
    static void writeArticalToXml(ArticalInterface &data, QString fileName);
signals:
    
public slots:
    
};

#endif // YZXMLWRITER_H
