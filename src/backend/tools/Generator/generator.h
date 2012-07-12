#ifndef GENERATOR_H
#define GENERATOR_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <iostream>
#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QDir>
#include "version.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = 0);
    void parseIndexFile();
    
signals:
    
public slots:
private slots:
private:
    void initParameters();

    //generate webroot
    void generateIndexFile(const QDomElement &element);
    QString m_indexFilePath;
    QMap<QString, QString> m_paramenters;

    QDir m_webrootDir;
};

#endif // GENERATOR_H
