#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{
    WebSite websiteItem;
    websiteItem.url = "http://www.harbin.gov.cn/";
    websiteItem.regExp = "";
    websiteItem.websiteName = "chinese harbin";
    Node nodeItem;
    nodeItem.url = "http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm";
    nodeItem.regExp = "<a .*href=\"([^\"]*)\" class=\"bgc1\" onmouseover=\"this.className=\'bgc2\'\" onmouseout=\"this.className=\'bgc1\'";
    Node childNodeItem;
    childNodeItem.nextPageRegExp="<a href=\"([^\"]*)\" class=\"Next\">下页";
    childNodeItem.regExp = "<a class=\"f3348\" href=\"([^\"]*)\"";
    childNodeItem.titleRegExp = "<a class=\"f3348\".*title=\"([^\"]*)\"";
    nodeItem.nodeList.append(childNodeItem);
    websiteItem.nodeList.append(nodeItem);
    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"config.xml");
    qDebug()<<"finish";
}
