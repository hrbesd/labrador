#include <QCoreApplication>
#include "forerunner.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ForeRunner forerunner;
    return a.exec();
}
