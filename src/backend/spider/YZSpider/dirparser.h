#ifndef DIRPARSER_H
#define DIRPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include "DataInterface.h"

class DirParser : public QObject
{
    Q_OBJECT
public:
    explicit DirParser(QObject *parent = 0);
    static void parseDirFile(QString dirFile, WebSite& website );
    static void parseNode(QXmlStreamReader& reader, WebSite& website );
    static void parseNodeList(QXmlStreamReader& reader, WebSite& website);
    static bool checkWhetherNodeExists(Node &nodeItem);
    static QString workerDir;
signals:
    
public slots:
    
};

#endif // DIRPARSER_H
