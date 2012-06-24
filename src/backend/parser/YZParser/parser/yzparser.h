#ifndef YZPARSER_H
#define YZPARSER_H

#include <QObject>
#include <QFile>
#include <QUrl>
#include <QRegExp>
#include <QDir>
#include "DataInterface.h"
#include "../xmlWriter/yzxmlwriter.h"
#include <QtScript>
#include <QTextStream>

class YZParser : public QObject
{
    Q_OBJECT

public:
    explicit YZParser(QObject *parent = 0);
    //success return 0, else return -1
    int parseFile(QString fileName);
    void parseFolder(QString folder);
    void parseImageFromBody(const QString& dataString,QString base, ArticleInterface& articleInterface);

signals:
    
public slots:
protected:
private:
    QScriptEngine m_engine;
    QScriptValue m_globalValue;
    QScriptValue m_parserValue;
};

#endif // YZPARSER_H
