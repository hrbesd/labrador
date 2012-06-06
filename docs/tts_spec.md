# Text-to-speech Web Service

*草稿*

*不完整*

## 目的
在云中建立一个SaaS，输入一段文字，转换成现代浏览器支持的格式的音频，输出URL，供其他服务调用。

## 功能

- 输入
	* 纯文本 __A__
	* SSML __AA__
- 输出
	* MP3 __A__
	* OGG __A__
	* AAC __AA__
	* WAV __AA__
	* SWF __AAA__
	
- 查询状态
	* 返回任务状态 __A__

## 实现
	
### 接口定义

*注意： 未设计验证机制*

#### 协议

* SOAP __A__
* REST __AA__

#### 方法

* Text2Speech() __A__
* Ssml2Speech() __A__
* GetStatus() __A__

#### 参数

- Text2Speech和Ssml2Speech
	* Plain text
	* Base64 encoded text __AA__

- GetStatus
	* JobID 或者 源文本的MD5 Hash

#### 返回

除了标准HTTP代码之外：

- Text2Speech和Ssml2Speech
	* JobID
	* URLs (Not ready upon response)
	
对应格式和男女，有多个URL。

- GetStaus	
	* 若干状态，分别表示（排队中，已合成，已转换，已上传，已知错误，未知错误）

### 负载管理

负载平衡管理以下三种类型的工作，通过监控队列，调整各类服务器实例的数量，保证平均流程完成时间低于N秒（N为人为配置的参数）。

*注意：以下三种类型的服务可能在同一个服务器内，也可能通过局域网或互联网连接*

### TTS Server

* 使用操作系统或其他商用TTS引擎搭建服务
* 如果产生临时文件，以文本的MD5 Hash结果命名
* 生成文件符合以下规范：

	- 采样：22KHz
	- 声道：单声道
	- 格式：见前面功能定义
	- 男声和女声（可以分别读标题和正文，根据用户配置）__AAA__
	- 分为慢、标准、快三个版本 __AA__

* 如果有需要，使用FTP等高效率的协议向下一阶段传送音频文件

### Transcoding Server 

* 以ffmpeg为平台搭建服务
* 如果产生临时文件，以文本的MD5 Hash结果命名
* 如果有需要，使用FTP等高效率的协议向下一阶段传送音频文件

### Web Server

Web Server提供静态音频文件的下载。文件以文本的MD5 Hash结果命名，也可用Hash的某种变形命名，以防止滥用。

*音频文件的目录结构有待定义。*

考虑到高负载和低延迟的要求，可能需要混合以下技术：

* 物理服务器
* AWS S3
* AWS EC2
* CDN

配置Web Server时，应鼓励用户代理使用长期缓存。

## 如何使用此服务

### 输入端
### 调用端

## 备注