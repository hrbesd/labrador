#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{   
    /*********************************************
     * harbin config file
     ********************************************/
    WebSite websiteItem;
    websiteItem.editor = "genghailong";
    websiteItem.info = "zhong guo haerbin";
    websiteItem.crawlTime = "";
    websiteItem.threadLimit = "10";
    websiteItem.node.url = "http://www.harbin.gov.cn/";
    websiteItem.node.name = "chinese harbin";
    /****************************************
     *公告页面规则
     *
     ****************************************/
    Rule* gongGaoRule = new Rule;  //公告总页面
    Rule* gongGaoChildRule = new Rule;  //公告年份分页面
    Rule* gongGaoArticleRule = new Rule;    //公告正文页面

    Node gongGaoNodeItem;
    gongGaoNodeItem.name = "zhengfugonggao";
    gongGaoNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm#";
    gongGaoNodeItem.ruleList.append(gongGaoChildRule);

    gongGaoRule->nodeList.append(gongGaoNodeItem);

    gongGaoChildRule->expressionList
            <<Expression("url"
                         ,"<a .*href=\"([^\"]*)\" class=\"bgc1\" onmouseover=\"this.className=\'bgc2\'\" onmouseout=\"this.className=\'bgc1\'")
           <<Expression("title"
                        ,"class=\"bgc1\" onmouseover=\"this.className='bgc2'\" .*<span>(.*)</span>");

    gongGaoArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\" class=\"Next\">下页";

    gongGaoArticleRule->expressionList
            <<Expression("url"
                         ,"<a class=\"f3348\" href=\"([^\"]*)\"")
           <<Expression("title"
                        ,"<a class=\"f3348\".*title=\"([^\"]*)\"");
    gongGaoChildRule->childRule = gongGaoArticleRule;
    websiteItem.node.ruleList.append(gongGaoRule);

    /*************************************
     *部门动态规则
     *
     ************************************/
    Rule* buMenDongTaiRule = new Rule;  //公告总页面
    Rule* buMenDongTaiChildRule = new Rule;  //公告年份分页面
    Rule* buMenDongTaiArticleRule = new Rule;    //公告正文页面

    Node buMenDongTaiNodeItem;
    buMenDongTaiNodeItem.name = "bumendongtai";
    buMenDongTaiNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/bmdt.htm";
    buMenDongTaiNodeItem.ruleList.append(buMenDongTaiChildRule);

    buMenDongTaiRule->nodeList.append(buMenDongTaiNodeItem);
    Expression buMenDongTaiChildUrlExpression;
    Expression buMenDongTaiChildTitleExpression;
    buMenDongTaiChildUrlExpression.label = "url";
    buMenDongTaiChildUrlExpression.value = "<a .*href=\"([^\"]*)\" class=\"hei14\">";
    buMenDongTaiChildTitleExpression.label = "title";
    buMenDongTaiChildTitleExpression.value = "<FONT class=\"hei12\">(.*)</font>";
    buMenDongTaiChildRule->expressionList<<buMenDongTaiChildUrlExpression<<buMenDongTaiChildTitleExpression;

    buMenDongTaiArticleRule->nextPageExpression.value="<a href=\"([^\"]*)\" class=\"Next\">下页";
    buMenDongTaiArticleRule->expressionList
            <<Expression("url"
                         ," <a class=\"f3665\" href=\"([^\"]*)\"")
           <<Expression("title"
                        ,"class=\"f3665\" title=\"([^\"]*)\"");
    buMenDongTaiChildRule->childRule = buMenDongTaiArticleRule;

    websiteItem.node.ruleList.append(buMenDongTaiRule);

    /**********************************************************
     *Beijing config file
     *********************************************************/
    //        WebSite websiteItem;
    //        websiteItem.editor = "genghailong";
    //        websiteItem.info = "beijing";
    //        websiteItem.crawlTime = "";
    //        websiteItem.threadLimit = "10";
    //        websiteItem.node.url = "http://www.beijing.gov.cn/";
    //        websiteItem.node.name = "chinese beijing";
    ///********************************
    // *热点关注
    // *******************************/
    //        Rule* gongGaoRule = new Rule;
    //        Rule* gongGaoArticleRule = new Rule;

    //        Node gongGaoNodeItem;
    //        gongGaoNodeItem.name = "redianguanzhu";
    //        gongGaoNodeItem.url = "http://www.beijing.gov.cn/sy/rdgz/";
    //        gongGaoNodeItem.ruleList.append(gongGaoArticleRule);

    //        gongGaoRule->nodeList.append(gongGaoNodeItem);

    //        gongGaoArticleRule->nextPageRegExp="<a href=\"([^\"]*)\" class=\"Next\">下页";
    //        gongGaoArticleRule->urlRegExp = "<td class=\"font14\">·<a href=\"([^\"]*)\"";
    //        gongGaoArticleRule->nameRegExp = "<td class=\"font14\">·<a href=\"[^\"]*\" target=\"_blank\">(.*)</a>";

    //        /*************************************
    //         *部门动态规则
    //         *
    //         ************************************/
    ////        Rule* buMenDongTaiRule = new Rule;  //公告总页面
    ////        Rule* buMenDongTaiChildRule = new Rule;  //公告年份分页面
    ////        Rule* buMenDongTaiArticleRule = new Rule;    //公告正文页面

    ////        Node buMenDongTaiNodeItem;
    ////        buMenDongTaiNodeItem.name = "bumendongtai";
    ////        buMenDongTaiNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/bmdt.htm";
    ////        buMenDongTaiNodeItem.ruleList.append(buMenDongTaiChildRule);

    ////        buMenDongTaiRule->nodeList.append(buMenDongTaiNodeItem);

    ////        buMenDongTaiChildRule->urlRegExp = "<a .*href=\"([^\"]*)\" class=\"hei14\">";
    ////        buMenDongTaiChildRule->nameRegExp = "<FONT class=\"hei12\">(.*)</font>";

    ////        buMenDongTaiArticleRule->nextPageRegExp="<a href=\"([^\"]*)\" class=\"Next\">下页";
    ////        buMenDongTaiArticleRule->urlRegExp = " <a class=\"f3665\" href=\"([^\"]*)\"";
    ////        buMenDongTaiArticleRule->nameRegExp = "class=\"f3665\" title=\"([^\"]*)\"";
    ////        buMenDongTaiChildRule->childRule = buMenDongTaiArticleRule;


    //        websiteItem.node.ruleList.append(gongGaoRule);
    ////        websiteItem.node.ruleList.append(buMenDongTaiRule);
    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"config.xml");
    qDebug()<<"finish";
}
