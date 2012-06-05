#include <QCoreApplication>
#include "./parser/harbingov/harbingovparser.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HarbinGovParser parser;
    parser.parseFile("99835969e94c247708d289b3d1ae9f02");
    return a.exec();
}
