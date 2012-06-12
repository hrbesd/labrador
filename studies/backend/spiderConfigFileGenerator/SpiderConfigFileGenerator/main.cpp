#include <QCoreApplication>
#include <QTextCodec>
#include "spiderconfigfilegenerator.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *tc=QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(tc);
    QTextCodec::setCodecForTr(tc);
    QTextCodec::setCodecForCStrings(tc);

    SpiderConfigFileGenerator generator;
    return a.exec();
}
