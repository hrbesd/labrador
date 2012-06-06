# Labrador项目快速原型技术说明书

*作者：Cliff Woo*

## 项目简述 ##

*摘自 Feature_Spec*

建立一个云端服务，无需改动客户的原始网站，自动获得网页集合，保留部分信息，生成一个新的网站，并符合无障碍标准。通过加入视觉辅助和语音朗读等工具，增强用户代理的可访问能力。设计此服务以开发迭代化、架构简单化、协作远程化、服务长期化为原则。

## 版本简述 ##

该版本力图在最短时间内完成一个快速原型设计，以验证基础架构及基本设计的合理性。

## 应用场景 ##
### 角色 ###
- 运营方
  * System Admin
  * Support
- 开发方
  * Developer
- 用户方：
  * User
### 术语 ###
* Site_URL_List :网站待改造的栏目及内容列表，快速原型模式下为逐行的白名单，每行包括一个网站的URL
* Labrador Storage：项目的存储系统，可以使用AWS的云服务模式，也可以采用单台服务器的存储。在快速原型模式下，暂时采用单机存储。
## 技术架构 ##

  * Labrador Spider：根据User或者System Admin提供的Site_URL_List，分析并下载网页，保存在Labrador Storage中
  * Labrador Analyzer: 分析下载的网页，并对网页进行分析，根据要求去除无关元素，保留正文，并保存为XML格式
  * Labrador Assembler: 将Analyzer处理过的XML文件，与定制的CSS组合，提供给用户浏览。
  * Labrador Toolbar: 在用户浏览页面中嵌入的工具条，提供放大、缩小、调整对比度、更换CSS等功能。
  * Labrador TTS Engine: 利用现有的TTS的接口，提供段落或全文的TTS服务。
  * Labrador Admin Console：提供给运营方或者最终用户来管理待改造网站的栏目及内容列表。在快速原型阶段暂时不做开发。
  
## 开发语言和工具 ##
- 开发语言
  * Labrador Spider：C++
  * Labrador Analyzer: C++
  * Labrador Toolbar: Javascript
  * Labrador TTS Engine:C++
  * Labrador Admin Console：Java
- 工具
  * Microsoft or Mac TTS Engine
## 基础设施平台 ##
- 测试服务器：

  *如果有需要，大家可以临时使用该服务器做为验证和测试服务器，后期我们考虑转向AWS平台*

  * Server Ip：219.217.227.120
  * User：git （sudouser）
  * Password:1q2w#E$R 
  * Web Root Dir: /var/www/labrador/
## 数据存储 ##
## 程序接口 ##
## 用户体验 ##
## 关键技术解决方案 ##
## 技术指标 ##
