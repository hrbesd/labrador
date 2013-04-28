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
#include <QStack>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = 0);
    
signals:
    
public slots:
private slots:
private:
    //init app parameters
    void initParameters();

    //generate webroot
    void generateWebroot();
//20130428
    QString generatePageTitle(const Node &node);      


   void generateIndexFile();
    void generateColumnFile(const Node &node);
    void generateListFile(const Node &node);
    void generateArticleFile(const Node &node);
    void generateFiles();
    //read xml files
    void parseWebsiteIndexFile();
    void parseWebsiteXml(QXmlStreamReader &reader);
    void parseNodeXml(QXmlStreamReader &reader, Node& node);
    void parseNodeListXml(QXmlStreamReader &reader,Node& node);

    //utilities
    void writeNodeListXml(QXmlStreamWriter &writer, const QList<Node>& nodeList);
    void writeNodeXml(QXmlStreamWriter &writer,const Node& node);
    void writeParentPageUrlXml(QXmlStreamWriter &writer,const Node& nodeItem);
    NodeType getNodeType(const Node& node);
    QXmlStreamReader xmlReader;
    QString m_indexFilePath;
    QMap<QString, QString> m_paramenters;
    WebSite m_website;
    QDir m_webrootDir;
    QStack<const Node*> m_nodeStack;
};

#endif // GENERATOR_H
