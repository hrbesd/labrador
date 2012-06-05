#include <QCoreApplication>
#include "yzspider.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    YZSpider spider;
    spider.downloadWebPage("http://www.harbin.gov.cn/info/news/index/detail1/314675.htm");
    return a.exec();
}
