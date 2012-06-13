#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{
    WebSite websiteItem;
    websiteItem.url = "http://www.harbin.gov.cn/";
    websiteItem.urlRegExp = "";
    websiteItem.name = "chinese harbin";
    Node nodeItem;
    nodeItem.name = "zhengfugonggao";
    nodeItem.url = "http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm";
    nodeItem.urlRegExp = "<a .*href=\"([^\"]*)\" class=\"bgc1\" onmouseover=\"this.className=\'bgc2\'\" onmouseout=\"this.className=\'bgc1\'";
    nodeItem.nameRegExp = "class=\"bgc1\" onmouseover=\"this.className='bgc2'\" .*<span>(.*)</span>";
    Node childNodeItem;
    childNodeItem.nextPageRegExp="<a href=\"([^\"]*)\" class=\"Next\">下页";
    childNodeItem.urlRegExp = "<a class=\"f3348\" href=\"([^\"]*)\"";
    childNodeItem.nameRegExp = "<a class=\"f3348\".*title=\"([^\"]*)\"";
    nodeItem.nodeList.append(childNodeItem);
    websiteItem.nodeList.append(nodeItem);
    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"config.xml");
    qDebug()<<"finish";
}
