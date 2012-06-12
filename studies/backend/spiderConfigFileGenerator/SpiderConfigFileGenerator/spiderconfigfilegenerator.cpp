#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{
    WebSite websiteItem;
    websiteItem.url = "http://www.harbin.gov.cn/";
    websiteItem.regExp = "";
    websiteItem.websiteName = "chinese harbin";
    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"config.xml");
    qDebug()<<"finish";
}
