#include <QCoreApplication>
#include "./parser/harbingov/harbingovparser.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HarbinGovParser parser;
    return a.exec();
}
