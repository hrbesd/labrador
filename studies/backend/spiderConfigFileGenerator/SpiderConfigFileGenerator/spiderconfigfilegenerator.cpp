#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{
    WebSite websiteItem;
    websiteItem.editor = "genghailong";
    websiteItem.info = "zhong guo haerbin";
    websiteItem.node.url = "http://www.harbin.gov.cn/";
    websiteItem.node.name = "chinese harbin";

    Rule* gongGaoRule = new Rule;  //公告总页面
    Rule* gongGaoChildRule = new Rule;  //公告年份分页面
    Rule* gongGaoArticleRule = new Rule;    //公告正文页面

    Node gongGaoNodeItem;
    gongGaoNodeItem.name = "zhengfugonggao";
    gongGaoNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm";
    gongGaoNodeItem.ruleList.append(gongGaoChildRule);

    gongGaoRule->nodeList.append(gongGaoNodeItem);

    gongGaoChildRule->urlRegExp = "<a .*href=\"([^\"]*)\" class=\"bgc1\" onmouseover=\"this.className=\'bgc2\'\" onmouseout=\"this.className=\'bgc1\'";
    gongGaoChildRule->nameRegExp = "class=\"bgc1\" onmouseover=\"this.className='bgc2'\" .*<span>(.*)</span>";

    gongGaoArticleRule->nextPageRegExp="<a href=\"([^\"]*)\" class=\"Next\">下页";
    gongGaoArticleRule->urlRegExp = "<a class=\"f3348\" href=\"([^\"]*)\"";
    gongGaoArticleRule->nameRegExp = "<a class=\"f3348\".*title=\"([^\"]*)\"";
    gongGaoChildRule->childRule = gongGaoArticleRule;

    websiteItem.node.ruleList.append(gongGaoRule);
    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"config.xml");
    qDebug()<<"finish";
}
