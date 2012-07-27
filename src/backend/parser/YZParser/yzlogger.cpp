#include "yzlogger.h"
#include <QByteArray>
YZLogger* YZLogger::logger = NULL;
QString YZLogger::logFilePath = "spider_log.txt";
YZLogger::YZLogger(QObject *parent) :
    QObject(parent)
{
    logFile.setFileName(YZLogger::logFilePath);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("can't open log File");
        return;
    }
}

YZLogger* YZLogger::Logger()
{
    if(YZLogger::logger==NULL) {
        YZLogger::logger = new YZLogger();
    }
    return YZLogger::logger;
}

void YZLogger::log(Type type, QString filePath, QString str)
{
    QStringList strList;
    strList.append("["+QDateTime::currentDateTime().toString(Qt::ISODate)+"]");
    if(type==YZLogger::Warning)
    {
        strList.append("[Warning]");
    }
    else if(type==YZLogger::Debug)
    {
        strList.append("[Debug]");
    }
    else if(type==YZLogger::Info)
    {
        strList.append("[Info]");
    }
    else if(type==YZLogger::Error)
    {
        strList.append("[Error]");
    }
    strList.append("["+filePath+"]");
    strList.append("["+str+"]");
    logFile.write(strList.join(" ").toUtf8());
    logFile.write("\n");
    logFile.flush();
}
