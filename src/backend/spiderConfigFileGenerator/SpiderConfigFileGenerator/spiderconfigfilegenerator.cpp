#include "spiderconfigfilegenerator.h"
#include <QDebug>

SpiderConfigFileGenerator::SpiderConfigFileGenerator(QObject *parent) :
    QObject(parent)
{   
    //        /*********************************************
    //         * harbin config file
    //         ********************************************/
    //        WebSite websiteItem;
    //        websiteItem.editor = "genghailong";
    //        websiteItem.info = "zhong guo haerbin";
    //        websiteItem.crawlTime = "";
    //        websiteItem.threadLimit = "10";
    //        websiteItem.node.url = "http://www.harbin.gov.cn/";
    //        websiteItem.node.name = "chinese harbin";
    //        /****************************************
    //         *公告页面规则
    //         *
    //         ****************************************/
    //        Rule* gongGaoRule = new Rule;  //公告总页面
    //        Rule* gongGaoChildRule = new Rule;  //公告年份分页面
    //        Rule* gongGaoArticleRule = new Rule;    //公告正文页面

    //        Node gongGaoNodeItem;
    //        gongGaoNodeItem.name = "zhengfugonggao";
    //        gongGaoNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm#";
    //        gongGaoNodeItem.ruleList.append(gongGaoChildRule);

    //        gongGaoRule->nodeList.append(gongGaoNodeItem);
    //        gongGaoChildRule->urlExpression.value = "<a .*href=\"([^\"]*)\" class=\"bgc1\" onmouseover=\"this.className=\'bgc2\'\" onmouseout=\"this.className=\'bgc1\'";
    //        gongGaoChildRule->titleExpression.value = "class=\"bgc1\" onmouseover=\"this.className='bgc2'\" .*<span>(.*)</span>";

    //        gongGaoArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\" class=\"Next\">下页";
    //        gongGaoArticleRule->urlExpression.value = "<a class=\"f3348\" href=\"([^\"]*)\"";
    //        gongGaoArticleRule->titleExpression.value = "<a class=\"f3348\".*title=\"([^\"]*)\"";

    //        gongGaoChildRule->childRule = gongGaoArticleRule;
    //        websiteItem.node.ruleList.append(gongGaoRule);

    //        /*************************************
    //         *部门动态规则
    //         *
    //         ************************************/
    //        Rule* buMenDongTaiRule = new Rule;  //公告总页面
    //        Rule* buMenDongTaiChildRule = new Rule;  //公告年份分页面
    //        Rule* buMenDongTaiArticleRule = new Rule;    //公告正文页面

    //        Node buMenDongTaiNodeItem;
    //        buMenDongTaiNodeItem.name = "bumendongtai";
    //        buMenDongTaiNodeItem.url = "http://www.harbin.gov.cn/zwxxgk/bmdt.htm";
    //        buMenDongTaiNodeItem.ruleList.append(buMenDongTaiChildRule);

    //        buMenDongTaiRule->nodeList.append(buMenDongTaiNodeItem);

    //        buMenDongTaiChildRule->urlExpression.value = "<a .*href=\"([^\"]*)\" class=\"hei14\">";
    //        buMenDongTaiChildRule->titleExpression.value = "<FONT class=\"hei12\">(.*)</font>";

    //        buMenDongTaiArticleRule->nextPageExpression.value="<a href=\"([^\"]*)\" class=\"Next\">下页";
    //        buMenDongTaiArticleRule->urlExpression.value = " <a class=\"f3665\" href=\"([^\"]*)\"";
    //        buMenDongTaiArticleRule->titleExpression.value = "class=\"f3665\" title=\"([^\"]*)\"";
    //        buMenDongTaiChildRule->childRule = buMenDongTaiArticleRule;

    //        websiteItem.node.ruleList.append(buMenDongTaiRule);

    //    /**********************************************************
    //     *Beijing config file
    //     *********************************************************/
    //    WebSite websiteItem;
    //    websiteItem.editor = "genghailong";
    //    websiteItem.info = "beijing";
    //    websiteItem.crawlTime = "";
    //    websiteItem.threadLimit = "10";
    //    websiteItem.node.url = "http://www.beijing.gov.cn/";
    //    websiteItem.node.name = "chinese beijing";
    //    /********************************
    //     *热点关注
    //     *******************************/
    //    Rule* reDianGuanZhuRule = new Rule;
    //    Rule* reDianGuanZhuArticleRule = new Rule;

    //    Node reDianGuanZhuNodeItem;
    //    reDianGuanZhuNodeItem.name = "redianguanzhu";
    //    reDianGuanZhuNodeItem.url = "http://www.beijing.gov.cn/sy/rdgz/";
    //    reDianGuanZhuNodeItem.ruleList.append(reDianGuanZhuArticleRule);

    //    reDianGuanZhuRule->nodeList.append(reDianGuanZhuNodeItem);

    //    reDianGuanZhuArticleRule->nextPageExpression.value="function getYZSpiderResult(content) {"
    //            "var result = new Array();"
    //            "var i = 1;"
    //            "for (i = 1; i <= 49; i++)"
    //            "{ result.push(\"http://www.beijing.gov.cn/sy/rdgz/default_\"+i+\".htm\"); }"
    //            "return result;"
    //            "}";
    //    reDianGuanZhuArticleRule->nextPageExpression.type="JavaScript";
    //    reDianGuanZhuArticleRule->nextPageExpression.executeOnlyOnce = "true";
    //    reDianGuanZhuArticleRule->urlExpression.value = "<td class=\"font14\">·<a href=\"([^\"]*)\"";
    //    reDianGuanZhuArticleRule->titleExpression.value = "<td class=\"font14\">·<a href=\"[^\"]*\" target=\"_blank\">(.*)</a>";

    //    /*************************************
    //    *政务直播规则
    //    ************************************/
    //    Rule* zhengWuZhiBoRule = new Rule;
    //    Rule* zhengWuZhiBoArticleRule = new Rule;
    //    Node zhengWuZhiBoNodeItem;
    //    zhengWuZhiBoNodeItem.name = "zhengWuZhiBo";
    //    zhengWuZhiBoNodeItem.url = "http://zhengwu.beijing.gov.cn/zwzb/";
    //    zhengWuZhiBoNodeItem.ruleList.append(zhengWuZhiBoArticleRule);

    //    zhengWuZhiBoRule->nodeList.append(zhengWuZhiBoNodeItem);

    //    zhengWuZhiBoArticleRule->nextPageExpression.value="function getYZSpiderResult(content) {"
    //            "var result = new Array();"
    //            "var i = 1;"
    //            "for (i = 1; i <= 7; i++)"
    //            "{ result.push(\"http://zhengwu.beijing.gov.cn/zwzb/default_\"+i+\".htm\"); }"
    //            "return result;"
    //            "}";
    //    zhengWuZhiBoArticleRule->nextPageExpression.type="JavaScript";
    //    zhengWuZhiBoArticleRule->nextPageExpression.executeOnlyOnce = "true";
    //    zhengWuZhiBoArticleRule->urlExpression.value = "<li><a href=\"([^\"]*)\" target=\"_blank\"";
    //    zhengWuZhiBoArticleRule->titleExpression.value = "<li><a href=\"[^\"]*\" target=\"_blank\" title=\"([^\"]*)\"";

    //    websiteItem.node.ruleList.append(reDianGuanZhuRule);
    //    websiteItem.node.ruleList.append(zhengWuZhiBoRule);

    /*****************************************************
     *中国黑龙江 config file
     ****************************************************/
    WebSite websiteItem;
    websiteItem.editor = "耿海龙";
    websiteItem.info = "黑龙江政府网站";
    websiteItem.crawlTime = "";
    websiteItem.threadLimit = "10";
    websiteItem.node.url = "http://www.hlj.gov.cn/";
    websiteItem.node.name = "中国黑龙江";

    /****************************************************
     *全省概况
     ***************************************************/
    Rule *quanShengGaiKuang = new Rule();
    Node quanShengGaiKuangNodeItem;
    quanShengGaiKuangNodeItem.name = "全省概况";
    quanShengGaiKuangNodeItem.url = "http://www.hlj.gov.cn/zjlj/";
    quanShengGaiKuang->nodeList.append(quanShengGaiKuangNodeItem);

    Rule *quanShengGaiKuangArticleRule = new Rule();


    websiteItem.node.ruleList.append(quanShengGaiKuang);
    /****************************************************
     *公告信息
     ***************************************************/
    Rule *gongGaoXinXiRule = new Rule();
    Rule* gongGaoXinXiArticleRule = new Rule;
    Node gongGaoXinXiNodeItem;
    gongGaoXinXiNodeItem.name = "公告信息";
    gongGaoXinXiNodeItem.url = "http://www.hlj.gov.cn/zwdt/ggxx/index.shtml";
    gongGaoXinXiNodeItem.ruleList.append(gongGaoXinXiArticleRule);

    gongGaoXinXiRule->nodeList.append(gongGaoXinXiNodeItem);

    gongGaoXinXiArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
    gongGaoXinXiArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";
    gongGaoXinXiArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
    websiteItem.node.ruleList.append(gongGaoXinXiRule);

    /****************************************************
     *政务要闻
     ***************************************************/
    Rule *zhengWuYaoWenRule = new Rule();
    Rule* zhengWuYaoWenArticleRule = new Rule;
    Node zhengWuYaoWenNodeItem;
    zhengWuYaoWenNodeItem.name = "zhengWuYaoWen";
    zhengWuYaoWenNodeItem.url = "http://www.hlj.gov.cn/zwdt/zwyw/index.shtml";
    zhengWuYaoWenNodeItem.ruleList.append(zhengWuYaoWenArticleRule);

    zhengWuYaoWenRule->nodeList.append(zhengWuYaoWenNodeItem);

    zhengWuYaoWenArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
    zhengWuYaoWenArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";
    zhengWuYaoWenArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
    websiteItem.node.ruleList.append(zhengWuYaoWenRule);

    /****************************************************
     *计划规划
     ***************************************************/
    Rule* jiHuaGuiHuaRule = new Rule;
    Rule* jiHuaGuiHuaChildRule = new Rule;
    Rule* jiHuaGuiHuaArticleRule = new Rule;

    Node jiHuaGuiHuaNodeItem;
    jiHuaGuiHuaNodeItem.name = "jiHuaGuiHua";
    jiHuaGuiHuaNodeItem.url = "http://www.hlj.gov.cn/zwdt/jhgh/index.shtml";
    jiHuaGuiHuaNodeItem.ruleList.append(jiHuaGuiHuaChildRule);

    jiHuaGuiHuaRule->nodeList.append(jiHuaGuiHuaNodeItem);
    jiHuaGuiHuaChildRule->urlExpression.value = "<a href=\"([^\"]*)\">更多";
    jiHuaGuiHuaChildRule->titleExpression.value = "<td class=\"ftit\">(.*)</td>";

    jiHuaGuiHuaArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
    jiHuaGuiHuaArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
    jiHuaGuiHuaArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";

    jiHuaGuiHuaChildRule->childRule = jiHuaGuiHuaArticleRule;
    websiteItem.node.ruleList.append(jiHuaGuiHuaRule);


    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"spider_config.xml");
    qDebug()<<"finish";
    exit(0);
}
