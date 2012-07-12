#include <QCoreApplication>
#include "generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Generator g;
    return a.exec();
}
