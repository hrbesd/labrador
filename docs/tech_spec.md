# Labrador项目快速原型技术说明书

*作者：Cliff Woo*

## 项目简述 

*摘自 Feature_Spec*

建立一个云端服务，无需改动客户的原始网站，自动获得网页集合，保留部分信息，生成一个新的网站，并符合无障碍标准。通过加入视觉辅助和语音朗读等工具，增强用户代理的可访问能力。设计此服务以开发迭代化、架构简单化、协作远程化、服务长期化为原则。

## 版本简述 

该版本力图在最短时间内完成一个快速原型设计，以验证基础架构及基本设计的合理性。

## 应用场景

### 角色 
- 运营方
  * System Admin
  * Support
- 开发方
  * Developer
- 用户方：
  * User
  
### 术语 
* Site_URL_List :网站待改造的栏目及内容列表，快速原型模式下为逐行的白名单，每行包括一个网站的URL
* Labrador Storage：项目的存储系统，可以使用AWS的云服务模式，也可以采用单台服务器的存储。在快速原型模式下，暂时采用单机存储。

## 技术架构 



整个项目根据规划包括如下六部分的内容，其中Labrador Admin Console部分在快速原型阶段暂不实现，其他部分根据快速原型要求做不同程度的实现。

![image] (http://footoo.org/wp-content/uploads/2012/06/labrator_workflow.jpeg)

  * Labrador Spider：根据User或者System Admin提供的Site_URL_List，分析并下载网页，保存在Labrador Storage中
  * Labrador Reactor: 完成下载页面的改造
  * Labrador Parser: 分析下载的网页，并对网页进行分析，根据要求去除无关元素，保留正文，并保存为XML格式
  * Labrador Assembler: 将Analyzer处理过的XML文件，与定制的CSS组合，提供给用户浏览。
  * Labrador Toolbar: 在用户浏览页面中嵌入的工具条，提供放大、缩小、调整对比度、更换CSS等功能。
  * Labrador TTS Engine: 利用现有的TTS的接口，提供段落或全文的TTS服务。
  * Labrador Admin Console：提供给运营方或者最终用户来管理待改造网站的栏目及内容列表。在快速原型阶段暂时不做开发。
  
## 开发语言和工具 
- 开发语言
  * Labrador Spider：C++ 
  * Labrador Parser: C++
  * Labrador Reactor: Python
  * Labrador Assembler: Python
  * Labrador Toolbar: Javascript
  * Labrador TTS Engine: C++
  * Labrador Admin Console：Java
  
- 工具
  * Microsoft or Mac TTS Engine
## 基础设施平台
- 测试服务器：

  *如果有需要，大家可以临时使用该服务器做为验证和测试服务器，后期我们考虑转向AWS平台*

  * Server Ip：219.217.227.120
  * OS: Ubuntu 11.04 
  * Kernel : 2.6.32
  * RAM: 2G
  * User：git （sudouser）
  * Password:1q2w#E$R 
  * Web Root Dir: /var/www/labrador/

## 数据存储 


## 技术指标 

 *以下系统的技术指标以快速原型要求为准，后续版本将进行补充调整*
 
### Labrador Spider
- 主要功能
 * 根据Site_Url_List中的列表，依次下载网页
 * 对于待下载网页进行链接分析，继续下载站内链接
 * 将下载的网页以树状结构保存在存储系统中，每个网站以独立目录区分，网站以其url做为目录名
 
- 输入：Site_Url_List
- 输出：以网站名命名的目录，目录中保存根据Site_Url_List下载的网页

### Labrador Analyzer 
- 主要功能
 * 去掉网页的交互部分
 * 去除网页中以修饰为目的的图片
 * 网页正文的中的图片单独保存，并提供第三方接口以供System Admin或者User进行编辑，补充其文字说明。（快速原型版仅需完成图片保存即可）
 * 去除网页中闪烁的部分
 * 保留布局标签、保留正文部分的<Strong>标签
 
- 输入 ：经过Labrador Spider处理过的网页
- 输出 ： XML格式文件，需要包括如下四部分内容：
<code>
  标题: title
  作者：author
  时间: lastModified
  正文：bodyData
  保存的XML全文标签使用 article
</code>

### Labrador Assembler:

- 简述

Labrador Assembler在系统中的主要任务是整合样式与数据，生成最终的展示页面。其主要功能包括：xml数据的读取；html模板、资源的读取；以及生成最终html页面内容。

- 主要功能

 * 设计通用的CSS文件
 * XML数据的读取:xml数据来自于Labrador Analyser。Assembler通过读取这些xml文件，来获取网页需要呈现的数据内容。
 * HTML模板、资源的读取: 由于系统最终是以网站的形式进行呈现，因此需要提供一些基本的html标签、元素，以及Labrador Toolbar的支持，这些是静态的，而且相对不变的，因此Assembler事先准备了一些模板、资源，而Assembler的任务则是在需要的时候读取这些内容。
 * 生成HTML页面：最终的页面是由一些相对不变的界面元素（由模板、资源提供）以及一些动态改变的内容（由xml文件提供）组成，而Assembler最重要的任务就是整合这二者，并将最终的文件进行相应呈现。

- 输入: 经Labrador Analyzer处理过的XML文件

- 输出：HTML 文件

- 实现策略

由于系统中相对不变的部分是界面的前台表现，这些资源可以替换，但是替换的频率较之动态显示的内容要低很多；除此之外，这些资源更多是由UI来提供，与后台的数据管理耦合较低。基于以上两者考虑，决定实现一套模板引擎，从而减少静态内容与动态内容的耦合性，之后如果需要替换界面的表现，只需要替换这些html相关的内容就可以了，增强了扩展性，减少了耦合性。
在实现方面，参考率Grovvy语言的表现形式，实现了最简单的标签表示，也就是任何包裹在"${}"这个组合中的内容都是需要替换的标签，而标签对应的内容则需要从xml文件中提取。
为了简化期间，默认使用名称作为索引，也就是说，如果在html页面中包含一个"${title}"的内容，那么在xml文件中，一定包含一个title元素。那么在生成html页面的时候，就将title的xml文件内容替换到"${title}"这个标签的位置处。


### Labrador Toolbar  

- 主要功能 
 * 可以放大/缩小 网页字体，暂时不对最大字体和最小字体进行限制(部分浏览器做了限制)。(放大/缩小网页字体，每个间隔的放大比例在快速原型版本里不做要求)
 * 提供辅助线功能，帮助用户准确的定位（辅助线的颜色在快速原型版本中不予考虑）
 * 提供对比度翻转服务，可以翻转为高对比度
 * 工具条通过cookie保留用户选项
 * 支持谷歌翻译，可以完成部分或者全文的中英文互译
 * 预定样式表的选择

 *放大镜功能在快速原型版中暂不考虑*
 *支持语音朗读：提供标准、快速、加快三种模式*
 *使用脚本控制音量*
 *进入网站的语音欢迎提示*
 *支持快捷键：跳入正文、跳入标题、工具条闪烁、通过键盘访问整个网页*

- 实现

### Labrador TTS Engine  
*参考 tts_spec.md*
### Labrador Admin Console  
*快速原型版暂不提供*

## 程序接口
## 用户体验
*快速原型系统，UX部分从略*

