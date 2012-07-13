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
#include "yzlogger.h"

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
    void generateWebroot();
    void generateIndexFile();

    //read xml files
    void parseWebsiteIndexFile();
    void parseWebsiteXml(QXmlStreamReader &reader);
    void parseNodeXml(QXmlStreamReader &reader, Node& node);
    void parseNodeListXml(QXmlStreamReader &reader, QList<Node>& nodeList);

    //utilities
    void writeNodeListXml(QXmlStreamWriter &writer, QList<Node>& nodeList);
    void writeNodeXml(QXmlStreamWriter &writer, Node& node);
    NodeType getNodeType(const Node& node);
    QXmlStreamReader xmlReader;
    QString m_indexFilePath;
    QMap<QString, QString> m_paramenters;
    WebSite m_website;
    QDir m_webrootDir;
};

#endif // GENERATOR_H
