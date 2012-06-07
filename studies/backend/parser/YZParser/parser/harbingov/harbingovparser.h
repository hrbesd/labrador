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
    void parseImageFromBody(const QString& dataString,QString base, ArticleInterface& articleInterface);
    void cleanBodyData(QString& bodyData);
    void removeTags(QString& bodyData, QList<QString> tagList);
    void removeTag(QString& bodyData, QString tag);
signals:
    
public slots:
    
};

#endif // HARBINGOVPARSER_H
