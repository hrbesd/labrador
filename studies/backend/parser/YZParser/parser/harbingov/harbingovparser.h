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
    void parseImageFromBody(QByteArray& data,QString base, ArticleInterface& articleInterface);
    void cleanBodyData(QByteArray& bodyData);
    void removeTags(QByteArray& bodyData, QList<QString> tagList);
signals:
    
public slots:
    
};

#endif // HARBINGOVPARSER_H
