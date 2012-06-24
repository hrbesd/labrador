#include <QCoreApplication>
#include "./parser/yzparser.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    YZParser parser;
    return a.exec();
}
