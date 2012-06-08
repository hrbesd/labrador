#include <QCoreApplication>
#include "yzspider.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    YZSpider spider;
    spider.parseUrlListFile("urlList.txt");
    return a.exec();
}
