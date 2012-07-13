#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "version.h"
#include "DataInterface.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = 0);
    
signals:
    
public slots:
private slots:
private:
    void initParameters();

    //generate webroot

    //read xml files
    void parseWebsiteIndexFile();
    void parseWebsiteXml(QXmlStreamReader &reader);
    void parseNodeXml(QXmlStreamReader &reader, Node& node);
    void parseNodeListXml(QXmlStreamReader &reader, QList<Node>& nodeList);

    QXmlStreamReader xmlReader;
    QString m_indexFilePath;
    QMap<QString, QString> m_paramenters;
    WebSite m_website;
    QDir m_webrootDir;
};

#endif // GENERATOR_H
