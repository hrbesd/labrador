#ifndef SPIDERCONFIGFILEGENERATOR_H
#define SPIDERCONFIGFILEGENERATOR_H

#include <QObject>
#include "DataInterface.h"
#include "core/xmlWriter/yzxmlwriter.h"

class SpiderConfigFileGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SpiderConfigFileGenerator(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SPIDERCONFIGFILEGENERATOR_H
