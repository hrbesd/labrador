# Labrador Alpha 2版技术说明书

*作者：Cliff Woo*

## 项目简述 

*摘自 Feature_Spec*

建立一个云端服务，无需改动客户的原始网站，自动获得网页集合，保留部分信息，生成一个新的网站，并符合无障碍标准。通过加入视觉辅助和语音朗读等工具，增强用户代理的可访问能力。设计此服务以开发迭代化、架构简单化、协作远程化、服务长期化为原则。

## 版本简述 

*参考[Alpha2功能说明书]() *

## 应用场景

### 角色 

*参考[Labrador技术说明书](https://github.com/zhf/labrador/blob/master/docs/tech_spec.md) *
  
### 术语 

*参考[Labrador技术说明书](https://github.com/zhf/labrador/blob/master/docs/tech_spec.md) *

## 技术架构 

*参考[Labrador技术说明书](https://github.com/zhf/labrador/blob/master/docs/tech_spec.md) *
  
## 开发语言和工具 

*参考[Labrador技术说明书](https://github.com/zhf/labrador/blob/master/docs/tech_spec.md) *

## 功能说明书 

 *以下系统的技术指标以Alpha2版要求为准*
 
### 测试数据 ###

 本次功能测试需要对gov_sites_a.txt 中的3个网站进行测试

### 兼容性测试 ###

 Toolbar 部分的测试要在如下的浏览器中通过
 * Chrome 14及以上
 * Firefox 7及以上
 * IE 7 及以上

### Labrador Spider

- 嵌入式脚本解释器支持Javascript，支持运营方人员使用正则表达式进行匹配
  
  具体设计参考 [Spider技术说明书](https://github.com/zhf/labrador/edit/master/docs/backend/spider_spec.md) Javascript解释器及规则部分

### Labrador Reactor

- Reactor基于配置文件来为网站设定过滤规则

  具体设计参考 [Parser技术说明书](https://github.com/zhf/labrador/blob/master/docs/backend/parser_spec.md) 




  
  



  


