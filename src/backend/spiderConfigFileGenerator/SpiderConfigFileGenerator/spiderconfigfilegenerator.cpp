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

//    /****************************************************
//     *全省概况
//     ***************************************************/
//    Rule *quanShengGaiKuang = new Rule();
//    Node quanShengGaiKuangNodeItem;
//    quanShengGaiKuangNodeItem.name = "全省概况";
//    quanShengGaiKuangNodeItem.url = "http://www.hlj.gov.cn/zjlj/";

//    Rule *quanShengGaiKuangArticleRule = new Rule();
//    quanShengGaiKuangArticleRule->urlExpression.type = "JavaScript";
//    quanShengGaiKuangArticleRule->urlExpression.executeOnlyOnce = "true";
//    quanShengGaiKuangArticleRule->urlExpression.value = "function getYZSpiderResult(content)"
//            "{"
//            "    var result = new Array();"
//            "	var startIndex = content.indexOf(\"<div class=\\\"slidingList_none\\\" id=\\\"slidingList2\\\" style=\\\"height:27px\\\">\");"
//            "    var endIndex = content.indexOf(\"</div>\",startIndex+1);"
//            "    var tmp = content.substring(startIndex,endIndex);"
//            "    var reg = new RegExp(\"<li> <a href=\\\"([^\\\"]*)\\\"\",\"g\");"
//            "    var regResult = reg.exec(tmp);"
//            "	while(reg.lastIndex!==0)"
//            "	{"
//            "		result.push(regResult[1]);"
//            "		regResult = reg.exec(tmp);"
//            "	}"
//            "    return result;"
//            "}";
//    quanShengGaiKuangArticleRule->titleExpression.type = "JavaScript";
//    quanShengGaiKuangArticleRule->titleExpression.executeOnlyOnce = "true";
//    quanShengGaiKuangArticleRule->titleExpression.value = "function getYZSpiderResult(content)"
//            "{"
//            "    var result = new Array();"
//            "	var startIndex = content.indexOf(\"<div class=\\\"slidingList_none\\\" id=\\\"slidingList2\\\" style=\\\"height:27px\\\">\");"
//            "    var endIndex = content.indexOf(\"</div>\",startIndex+1);"
//            "    var tmp = content.substring(startIndex,endIndex);"
//            "    var reg = new RegExp(\"<li> <a href=\\\"[^>]*>([^<]*)<\",\"g\");"
//            "    var regResult = reg.exec(tmp);"
//            "	while(reg.lastIndex!==0)"
//            "	{"
//            "		result.push(regResult[1]);"
//            "		regResult = reg.exec(tmp);"
//            "	}"
//            "    return result;"
//            "}";

//    quanShengGaiKuangNodeItem.ruleList.append(quanShengGaiKuangArticleRule);
//    quanShengGaiKuang->nodeList.append(quanShengGaiKuangNodeItem);
//    websiteItem.node.ruleList.append(quanShengGaiKuang);

//    /*****************************************************
//     *投资
//     ****************************************************/
//    Rule* touZi = new Rule();
//    Node touZiNodeItem;
//    touZiNodeItem.name="投资";
//    touZiNodeItem.url = "http://www.hlj.gov.cn/tzlj/";

//    Rule* touZiChildRule = new Rule();
//    touZiChildRule->urlExpression.type = "JavaScript";
//    touZiChildRule->urlExpression.executeOnlyOnce = "true";
//    touZiChildRule->urlExpression.value = "function getYZSpiderResult(content)"
//            "{"
//            "    var result = new Array();"
//            "	var startIndex = content.indexOf(\"<div class=\\\"slidingList_none\\\" id=\\\"slidingList9\\\" style=\\\"height:27px;padding-left:200px\\\">\");"
//            "    var endIndex = content.indexOf(\"</div>\",startIndex+1);"
//            "    var tmp = content.substring(startIndex,endIndex);"
//            "    var reg = new RegExp(\"<li> <a href=\\\"([^\\\"]*)\\\"\",\"g\");"
//            "    var regResult = reg.exec(tmp);"
//            "	while(reg.lastIndex!==0)"
//            "	{"
//            "		result.push(regResult[1]);"
//            "		regResult = reg.exec(tmp);"
//            "	}"
//            "    return result;"
//            "}";
//    touZiChildRule->titleExpression.type = "JavaScript";
//    touZiChildRule->titleExpression.executeOnlyOnce = "true";
//    touZiChildRule->titleExpression.value = "function getYZSpiderResult(content)"
//            "{"
//            "    var result = new Array();"
//            "	var startIndex = content.indexOf(\"<div class=\\\"slidingList_none\\\" id=\\\"slidingList9\\\" style=\\\"height:27px;padding-left:200px\\\">\");"
//            "    var endIndex = content.indexOf(\"</div>\",startIndex+1);"
//            "    var tmp = content.substring(startIndex,endIndex);"
//            "    var reg = new RegExp(\"<li> <a href=\\\"[^>]*>([^<]*)<\",\"g\");"
//            "    var regResult = reg.exec(tmp);"
//            "	while(reg.lastIndex!==0)"
//            "	{"
//            "		result.push(regResult[1]);"
//            "		regResult = reg.exec(tmp);"
//            "	}"
//            "    return result;"
//            "}";

//    Rule * touZiArticleChildRule = new Rule();
//    touZiArticleChildRule->urlExpression.value = "<td><ul><li><a href=\"([^\"]*)\"";
//    touZiArticleChildRule->titleExpression.value = "<td><ul><li><a href=[^>]*>([^<]*)<";
//    touZiArticleChildRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
//    touZiChildRule->childRule = touZiArticleChildRule;
//    //投资指南
//    Node touZiZhiNanNodeItem;
//    touZiZhiNanNodeItem.name="投资指南";
//    touZiZhiNanNodeItem.url="http://www.hlj.gov.cn/tzlj/tzzn/";
//    Rule *touZiZhiNanRule = new Rule();
//    Node banShiZhiNanNodeItem;
//    banShiZhiNanNodeItem.name="办事指南";
//    banShiZhiNanNodeItem.url="http://www.hlj.gov.cn/tzlj/tzzn/bszn/";
//    Node zaiXianBanLiNodeItem;
//    zaiXianBanLiNodeItem.name="在线办理";
//    zaiXianBanLiNodeItem.url="http://www.hlj.gov.cn/tzlj/tzzn/zxbl/";
//    touZiZhiNanRule->nodeList.append(banShiZhiNanNodeItem);
//    touZiZhiNanRule->nodeList.append(zaiXianBanLiNodeItem);
//    touZiZhiNanRule->childRule=touZiArticleChildRule;
//    touZiZhiNanNodeItem.ruleList.append(touZiZhiNanRule);
//    touZiChildRule->nodeList.append(touZiZhiNanNodeItem);

//    touZiNodeItem.ruleList.append(touZiChildRule);
//    touZi->nodeList.append(touZiNodeItem);
//    websiteItem.node.ruleList.append(touZi);

//    /****************************************************
//     *旅游
//     ***************************************************/
//    Rule* lvYou = new Rule();
//    Node lvYouNodeItem;
//    lvYouNodeItem.name="旅游";
//    lvYouNodeItem.url = "http://www.hlj.gov.cn/cylj/";

//    Rule* lvYouChildRule = new Rule();
//    Node lvYouXinXiNodeItem;
//    lvYouXinXiNodeItem.name="旅游信息";
//    lvYouXinXiNodeItem.url = "http://www.hlj.gov.cn/cylj/lvxx/";
//    Node lvYouShengJingNodeItem;
//    lvYouShengJingNodeItem.name="旅游胜景";
//    lvYouShengJingNodeItem.url = "http://www.hlj.gov.cn/cylj/lysj/";
//    Node lvYouJingGuanNodeItem;
//    lvYouJingGuanNodeItem.name="旅游景观";
//    lvYouJingGuanNodeItem.url = "http://www.hlj.gov.cn/cylj/lyjg/";
//    Node minSuFengQingNodeItem;
//    minSuFengQingNodeItem.name="民俗风情";
//    minSuFengQingNodeItem.url = "http://www.hlj.gov.cn/cylj/msfq/";
//    Node lvYouChangShiNodeItem;
//    lvYouChangShiNodeItem.name="旅游常识";
//    lvYouChangShiNodeItem.url = "http://www.hlj.gov.cn/cylj/lycs/";
//    Node canYinFuWuNodeItem;
//    canYinFuWuNodeItem.name="餐饮服务";
//    canYinFuWuNodeItem.url = "http://www.hlj.gov.cn/cylj/cyfw/";
//    Node longJiangGouWuNodeItem;
//    longJiangGouWuNodeItem.name="龙江购物";
//    longJiangGouWuNodeItem.url = "http://www.hlj.gov.cn/cylj/ljgw/";
//    Node lvYouXianLuNodeItem;
//    lvYouXianLuNodeItem.name="旅游线路";
//    lvYouXianLuNodeItem.url = "http://www.hlj.gov.cn/cylj/lyxl/";
//    Node longJiangTeChanNodeItem;
//    longJiangTeChanNodeItem.name="龙江特产";
//    longJiangTeChanNodeItem.url = "http://www.hlj.gov.cn/cylj/ljtc/";
//    Node liShiZhongDeHeiLongJiangNodeItem;
//    liShiZhongDeHeiLongJiangNodeItem.name="历史中的黑龙江";
//    liShiZhongDeHeiLongJiangNodeItem.url = "http://www.hlj.gov.cn/cylj/lslj/";
//    Node touSuJiGouNodeItem;
//    touSuJiGouNodeItem.name="投诉机构";
//    touSuJiGouNodeItem.url = "http://www.hlj.gov.cn/cylj/tsjg/";

//    Rule * lvYouArticleChildRule = new Rule();
//    lvYouArticleChildRule->urlExpression.value = "<td><ul><li><a href=\"([^\"]*)\"";
//    lvYouArticleChildRule->titleExpression.value = "<td><ul><li><a href=[^>]*>([^<]*)<";
//    lvYouArticleChildRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
//    Rule *lvYouPictureChildRule = new Rule();
//    lvYouPictureChildRule->urlExpression.value="<td width=\"33%\"><div align=\"center\"><a href=([^ ]*) ";
//    lvYouPictureChildRule->titleExpression.value="<div align=\"center\"><a href=[^ ]* Title=\"([^\"]*)\"";
//    lvYouPictureChildRule->nextPageExpression.value="<a href=\"([^\"]*)\">下一页";


//    lvYouXinXiNodeItem.ruleList.append(lvYouArticleChildRule);
//    lvYouShengJingNodeItem.ruleList.append(lvYouPictureChildRule);
//    lvYouJingGuanNodeItem.ruleList.append(lvYouPictureChildRule);
//    minSuFengQingNodeItem.ruleList.append(lvYouPictureChildRule);
//    lvYouChangShiNodeItem.ruleList.append(lvYouArticleChildRule);
//    lvYouXianLuNodeItem.ruleList.append(lvYouArticleChildRule);
//    longJiangTeChanNodeItem.ruleList.append(lvYouArticleChildRule);
//    liShiZhongDeHeiLongJiangNodeItem.ruleList.append(lvYouArticleChildRule);
//    touSuJiGouNodeItem.ruleList.append(lvYouArticleChildRule);

//    lvYouChildRule->nodeList.append(lvYouXinXiNodeItem);
//    lvYouChildRule->nodeList.append(lvYouShengJingNodeItem);
//    lvYouChildRule->nodeList.append(lvYouJingGuanNodeItem);
//    lvYouChildRule->nodeList.append(minSuFengQingNodeItem);
//    lvYouChildRule->nodeList.append(lvYouChangShiNodeItem);
//    lvYouChildRule->nodeList.append(canYinFuWuNodeItem);
//    lvYouChildRule->nodeList.append(longJiangGouWuNodeItem);
//    lvYouChildRule->nodeList.append(lvYouXianLuNodeItem);
//    lvYouChildRule->nodeList.append(longJiangTeChanNodeItem);
//    lvYouChildRule->nodeList.append(liShiZhongDeHeiLongJiangNodeItem);
//    lvYouChildRule->nodeList.append(touSuJiGouNodeItem);

//    lvYouNodeItem.ruleList.append(lvYouChildRule);
//    lvYou->nodeList.append(lvYouNodeItem);
//    websiteItem.node.ruleList.append(lvYou);

    /******************************************************
     *政务公开
     *****************************************************/
    Rule * zhengWuGongKai = new Rule();
    Node ZhengWuGongKaiNodeItem;
    ZhengWuGongKaiNodeItem.name="政务公开";
    ZhengWuGongKaiNodeItem.url="http://www.hlj.gov.cn/zwdt/index.shtml";

    Rule* zhengWuGongKaiChildRule = new Rule();
    Rule* zhengWuGongKaiChildArticleRule=new Rule();
    zhengWuGongKaiChildArticleRule->urlExpression.value="<td><ul><a href=\"([^\"]*)\"";
    zhengWuGongKaiChildArticleRule->titleExpression.value="<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";
    zhengWuGongKaiChildArticleRule->nextPageExpression.value="<a href=\"([^\"]*)\">下一页";
    zhengWuGongKaiChildRule->childRule=zhengWuGongKaiChildArticleRule;
    Rule* zhengWuGongKaiChildColumnRule=new Rule();
    zhengWuGongKaiChildColumnRule->urlExpression.value="<td align=\"right\" class=\"f12black\"><a href=\"([^\"]*)\"";
    zhengWuGongKaiChildColumnRule->titleExpression.value="<td class=\"ftit\">([^<]*)<";

    Node jiGouSheZhiNodeItem;
    jiGouSheZhiNodeItem.name="机构设置";
    jiGouSheZhiNodeItem.url="http://www.hlj.gov.cn/jgsz/index.shtml";

    Rule* jiGouSheZhiRule = new Rule();
    jiGouSheZhiRule->urlExpression.value="<td.* height=\"\\d\\d\"[^>]*><a href=\"([^\"]*)\"";
    jiGouSheZhiRule->titleExpression.value="<td.* height=\"\\d\\d\"[^>]*><a href=\"[^\"]*\"[^>]*>([^<]*)<";
    jiGouSheZhiNodeItem.ruleList.append(jiGouSheZhiRule);

    Node lingDaoJieShaoNodeItem;
    lingDaoJieShaoNodeItem.name="领导介绍";
    lingDaoJieShaoNodeItem.url="http://www.hlj.gov.cn/zwdt/lddt/";

    Rule* lingDaoJieShaoRule = new Rule();
    lingDaoJieShaoRule->titleExpression.value="<td align=\"center\" class=\"f12black\">([^<]*)</td";
    lingDaoJieShaoRule->urlExpression.value="<a href=\"([^\"]*)\"><img src=\"/zwdt/lddt/images/pic_zfw_lddt_jj.gif\"";
    lingDaoJieShaoNodeItem.ruleList.append(lingDaoJieShaoRule);

    Node zhengFuWenJianNodeItem;
    Rule *zhengFuWenJianRule = new Rule();

    Node shengZhengFuWenJianNodeItem;
    shengZhengFuWenJianNodeItem.name="省政府文件";
    shengZhengFuWenJianNodeItem.url="http://www.hlj.gov.cn/wjfg/zfwj/szwj/";
    Node shengZhengFuBanGongTingWenJianNodeItem;
    shengZhengFuBanGongTingWenJianNodeItem.name="省政府办公厅文件";
    shengZhengFuBanGongTingWenJianNodeItem.url="http://www.hlj.gov.cn/wjfg/zfwj/sbwj/";
    Node shengZhengFuLingNodeItem;
    shengZhengFuLingNodeItem.name="省政府令";
    shengZhengFuLingNodeItem.url="http://www.hlj.gov.cn/wjfg/zfwj/szfl/";
    Node shengZhiBuMenWenJianNodeItem;
    shengZhiBuMenWenJianNodeItem.name="省直部门文件";
    shengZhiBuMenWenJianNodeItem.url="http://www.hlj.gov.cn/gkml/zfxx/szwj/";

    zhengFuWenJianRule->nodeList.append(shengZhengFuWenJianNodeItem);
    zhengFuWenJianRule->nodeList.append(shengZhengFuBanGongTingWenJianNodeItem);
    zhengFuWenJianRule->nodeList.append(shengZhengFuLingNodeItem);
    zhengFuWenJianRule->nodeList.append(shengZhiBuMenWenJianNodeItem);
    zhengFuWenJianRule->childRule=zhengWuGongKaiChildArticleRule;
    zhengFuWenJianNodeItem.ruleList.append(zhengFuWenJianRule);

    Node faLvFaGuiNodeItem;
    Rule* faLvFaGuiRule= new Rule();

    Node guoJiaFaLvFaGuiNodeItem;
    guoJiaFaLvFaGuiNodeItem.name="国家法律法规";
    guoJiaFaLvFaGuiNodeItem.url="http://www.hlj.gov.cn/wjfg/flfg/gjfg/";
    Node diFangXingFaGuiNodeItem;
    diFangXingFaGuiNodeItem.name="地方性法规及政府规章";
    diFangXingFaGuiNodeItem.url="http://www.hlj.gov.cn/wjfg/flfg/dfgz/";
    faLvFaGuiRule->nodeList.append(guoJiaFaLvFaGuiNodeItem);
    faLvFaGuiRule->nodeList.append(diFangXingFaGuiNodeItem);
    faLvFaGuiRule->childRule=zhengWuGongKaiChildArticleRule;
    faLvFaGuiNodeItem.ruleList.append(faLvFaGuiRule);




    //    /****************************************************
//     *公告信息
//     ***************************************************/
//    Rule *gongGaoXinXiRule = new Rule();
//    Rule* gongGaoXinXiArticleRule = new Rule;
//    Node gongGaoXinXiNodeItem;
//    gongGaoXinXiNodeItem.name = "公告信息";
//    gongGaoXinXiNodeItem.url = "http://www.hlj.gov.cn/zwdt/ggxx/index.shtml";
//    gongGaoXinXiNodeItem.ruleList.append(gongGaoXinXiArticleRule);

//    gongGaoXinXiRule->nodeList.append(gongGaoXinXiNodeItem);

//    gongGaoXinXiArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
//    gongGaoXinXiArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";
//    gongGaoXinXiArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
//    websiteItem.node.ruleList.append(gongGaoXinXiRule);

//    /****************************************************
//     *政务要闻
//     ***************************************************/
//    Rule *zhengWuYaoWenRule = new Rule();
//    Rule* zhengWuYaoWenArticleRule = new Rule;
//    Node zhengWuYaoWenNodeItem;
//    zhengWuYaoWenNodeItem.name = "zhengWuYaoWen";
//    zhengWuYaoWenNodeItem.url = "http://www.hlj.gov.cn/zwdt/zwyw/index.shtml";
//    zhengWuYaoWenNodeItem.ruleList.append(zhengWuYaoWenArticleRule);

//    zhengWuYaoWenRule->nodeList.append(zhengWuYaoWenNodeItem);

//    zhengWuYaoWenArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
//    zhengWuYaoWenArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";
//    zhengWuYaoWenArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
//    websiteItem.node.ruleList.append(zhengWuYaoWenRule);

//    /****************************************************
//     *计划规划
//     ***************************************************/
//    Rule* jiHuaGuiHuaRule = new Rule;
//    Rule* jiHuaGuiHuaChildRule = new Rule;
//    Rule* jiHuaGuiHuaArticleRule = new Rule;

//    Node jiHuaGuiHuaNodeItem;
//    jiHuaGuiHuaNodeItem.name = "jiHuaGuiHua";
//    jiHuaGuiHuaNodeItem.url = "http://www.hlj.gov.cn/zwdt/jhgh/index.shtml";
//    jiHuaGuiHuaNodeItem.ruleList.append(jiHuaGuiHuaChildRule);

//    jiHuaGuiHuaRule->nodeList.append(jiHuaGuiHuaNodeItem);
//    jiHuaGuiHuaChildRule->urlExpression.value = "<a href=\"([^\"]*)\">更多";
//    jiHuaGuiHuaChildRule->titleExpression.value = "<td class=\"ftit\">(.*)</td>";

//    jiHuaGuiHuaArticleRule->nextPageExpression.value = "<a href=\"([^\"]*)\">下一页";
//    jiHuaGuiHuaArticleRule->urlExpression.value = "<td><ul><a href=\"([^\"]*)\"";
//    jiHuaGuiHuaArticleRule->titleExpression.value = "<td><ul><a href=\"[^\"]*\" Title=\"([^\"]*)\"";

//    jiHuaGuiHuaChildRule->childRule = jiHuaGuiHuaArticleRule;
//    websiteItem.node.ruleList.append(jiHuaGuiHuaRule);


    YZXmlWriter::writeWebsiteItemToXml(websiteItem,"spider_config.xml");
    qDebug()<<"finish";
    exit(0);
}
