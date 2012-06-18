#include "yzlogger.h"
#include <QByteArray>
YZLogger* YZLogger::logger = NULL;
YZLogger::YZLogger(QObject *parent) :
    QObject(parent)
{
    logFile.setFileName("spider_log.txt");
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

void YZLogger::log(QString str)
{
    logFile.write(str.toUtf8());
    logFile.write("\n");
}
