#ifndef YZPARSER_H
#define YZPARSER_H

#include <QObject>
#include <QFile>
#include <QUrl>
#include <iostream>
#include <QRegExp>
#include <QDir>
#include <QMap>
#include "DataInterface.h"
#include "../xmlWriter/yzxmlwriter.h"
#include <QtScript>
#include <QTextStream>

#include "version.h"
#include "yzlogger.h"
using namespace std;
class YZParser : public QObject
{
    Q_OBJECT

public:
    explicit YZParser(QObject *parent = 0);
    //success return 0, else return -1
    int parseFile(QString fileName);
    void parseFolder(QString folder);
    void parseImageFromBody(const QString& dataString,QString base, ArticleInterface& articleInterface);
    void parseConfigFile(QString parserConfigFileUrl);
signals:
    
public slots:
protected:
private:
    //init
    void initParameters();

    QScriptEngine m_engine;
    QScriptValue m_globalValue;
    QScriptValue m_parserValue;
    quint64 m_webpageCount;
    QMap<QString, QString> m_paramenters;
};

#endif // YZPARSER_H
