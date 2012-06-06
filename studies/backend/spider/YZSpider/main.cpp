#include <QCoreApplication>
#include "yzspider.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    YZSpider spider;
    spider.parseLinks("http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm");
    return a.exec();
}
