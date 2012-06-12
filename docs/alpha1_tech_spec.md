# Labrador Alpha1版技术说明书

*作者：Cliff Woo*

## 项目简述 

*摘自 Feature_Spec*

建立一个云端服务，无需改动客户的原始网站，自动获得网页集合，保留部分信息，生成一个新的网站，并符合无障碍标准。通过加入视觉辅助和语音朗读等工具，增强用户代理的可访问能力。设计此服务以开发迭代化、架构简单化、协作远程化、服务长期化为原则。

## 版本简述 

在原型系统的基础上，进一步确认技术方案，集中改善Spider部分的设计，并增强Toolbar的功能。

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

  * Labrador Spider：根据User或者System Admin提供的Site_URL_List，分析并下载网页，保存在Labrador Storage中
  * Labrador Analyzer: 分析下载的网页，并对网页进行分析，根据要求去除无关元素，保留正文，并保存为XML格式
  * Labrador Assembler: 将Analyzer处理过的XML文件，与定制的CSS组合，提供给用户浏览。
  * Labrador Toolbar: 在用户浏览页面中嵌入的工具条，提供放大、缩小、调整对比度、更换CSS等功能。
  * Labrador TTS Engine: 利用现有的TTS的接口，提供段落或全文的TTS服务。
  * Labrador Admin Console：提供给运营方或者最终用户来管理待改造网站的栏目及内容列表。在快速原型阶段暂时不做开发。
  
## 开发语言和工具 
- 开发语言
  * Labrador Spider：C++ 
  * Labrador Analyzer: C++ （or Python）
  * Labrador Assembler: Python
  * Labrador Toolbar: Javascript
  * Labrador TTS Engine: C++
  * Labrador Admin Console：Java
  
- 工具
  *  Mac TTS Engine

## 功能说明书 

 *以下系统的技术指标以Alpha1版要求为准*
 
### 测试数据 ###

 本次功能测试需要对gov_sites_a.txt 中的十个网站进行测试

### 兼容性测试 ###

 Toolbar 部分的测试要在如下的浏览器中通过
 * Chrome 14及以上
 * Firefox 7及以上
 * IE 7 及以上

### Labrador Spider

- Site_Url_List格式采用XML格式
- 嵌入式脚本脚本解释器支持Javascript，支持运营方人员使用正则表达式进行匹配

### Labrador Analyzer 

-  增加日志：日志包括如下三部分
  * 错误类型
  * 时间戳
  * 错误信息

- 实现断句，增加span标签。span标签加id，class id为文字内容的hash，class为yz_sentence
- 生成导航栏目 ：一级结构使用XML存储

### Labrador Assembler:

- 根据Analyzer生成的导航栏目生成栏目列表
- 栏目列表采用竖向排列、可以选择页面宽度(宽中窄)

### Labrador Toolbar  

- 快捷键系统设计
  
  * 采用动态绑定方式完成快捷键绑定

- 设计缺省的快捷键绑定，快捷键系统支持工具栏的全部功能，同时需要支持焦点跳转
  
- 键盘操作

  * 支持快捷键增强图片的对比度
  * 键盘操作有声响反馈

- 导航与浏览

  * 焦点可见并被强调
  * 焦点可以被脚本获知、记忆和恢复
  * 用户可以打开当前网页中所有大标题列表和链接列表，通过选择直接跳转焦点
  * 上述列表中的大小标题以缩进和/或字号有所区分
  * 上下文变化时有声响或语音提示(可以通过快捷键激活)
  * 如果网页内有正文，焦点起始位置默认为正文标题

  
- 工具栏

  * 可以快捷键打开、关闭工具栏
  * 增加放大镜功能
  * 工具栏提供帮助文档，帮助文档有语音解说
  * 帮助文档可以通过快捷键组合激活或者隐藏，使用后不会改变焦点位置
  * 可以调整行间距
  * 通过快捷键提高和减少图片的对比度
  * 点击后语音提示
  * 正文翻译
  * 段落阅读（按句号断句）
  * 翻译内容缓存
  * 翻译结果显示在单独的layer中
  * 网页对比度翻转(包括图片对比度翻转)
  * 仿照VoiceOver，实现对links，headings的朗读
  

- 声响反馈

  * 操作工具栏
  * 进入导航区域
  * 进入正文区域

- 用户代理(浏览器)

  * 生成的网页兼容，Chrome、Firefox、IE7及以上的浏览器
  
### Labrador TTS Engine  
*参考 tts_spec.md*
TTS Engine部分由e时代张建宗完成，目前该Web Service暂不考虑安全及用户认证问题
### Labrador Admin Console  
*Alpha1版暂不提供*


