#ifndef YZLOGGER_H
#define YZLOGGER_H

#include <QObject>
#include <QStringList>
#include <QDateTime>
#include <QFile>

class YZLogger : public QObject
{
    Q_OBJECT

public:
    enum Type{
        Info,
        Warning,
        Debug,
        Error
    };
    static YZLogger* Logger();
    void log(Type type, QString filePath, QString str);
    static QString logFilePath;
private:
    static YZLogger *logger;
    explicit YZLogger(QObject *parent = 0);
    QFile logFile;
signals:
    
public slots:
    
};

#endif // YZLOGGER_H
