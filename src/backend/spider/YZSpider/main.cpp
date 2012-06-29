#include <QCoreApplication>
#include "yzspider.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    YZSpider spider;
    spider.parseWebsiteConfigFile("config.xml");
    return a.exec();
}
