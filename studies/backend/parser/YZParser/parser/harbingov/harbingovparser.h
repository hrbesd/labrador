#ifndef HARBINGOVPARSER_H
#define HARBINGOVPARSER_H

#include "../yzparser.h"

class HarbinGovParser : public YZParser
{
    Q_OBJECT
public:
    explicit HarbinGovParser(QObject *parent = 0);
    virtual int parseFile(QString fileName);
    void parseFolder(QString folder);
signals:
    
public slots:
    
};

#endif // HARBINGOVPARSER_H