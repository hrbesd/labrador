#ifndef YZLOGGER_H
#define YZLOGGER_H

#include <QObject>
#include <QFile>

class YZLogger : public QObject
{
    Q_OBJECT
public:
    static YZLogger* Logger();
    void log(QString str);
    static QString logFilePath;
private:
    static YZLogger *logger;
    explicit YZLogger(QObject *parent = 0);
    QFile logFile;
signals:
    
public slots:
    
};

#endif // YZLOGGER_H
