# Reactor模块技术说明

*不完整*

*可用来指导实现*

## 目的

实现需求文档中```网页改造```部分。

## 接口

工作流程：

- 前：Parser
	* 目前在同一个主机运行，通过文件系统共享XML数据库
	* 今后计划拓展出独立的网络接口（FTP或Web Service）
- 后：Assembler
	* 目前与Assembler原有的接口形式不变
	
## 改造

从以下三方面入手改造:

* 无障碍化
* 标准化
* 结构化和语义化

### 无障碍化

*注：相当于目前的 `HarbinGovParser::cleanBodyData`*

* 检测到下列标签，直接删除标签： __A__
	- `<!--...-->` (内置脚本的另行判断)
	
* 检测到下列标签，在日志中留下警告，并可根据设置选择性删除： __A__

	- 缺失`alt`属性`<img>`
	- `<applet>`
	- `<area>`
	- `<map>`
	- `<iframe>`
	- `<script>`
	- `<style>`
	- `<object>`
	- `<audio>`和`<video>`
	- `type`属性是`audio`或`video`的`<embed>`
	- 带有`action`属性的`<form>`
	- 内容空白的`<canvas>`

* 检测到下列标签，在日志中留下警告： __AA__

	- 缺失`summary`的`<table>`
	- 太小的`<textarea>` (`rows` ≤ 3, `cols` ≤ 20)
	- `<figure>`
	- `<bb>`

* 根据元素的Id查找人工数据库: __AA__
	- 增加或替换`<img>`的`alt`内容
	- 在`<object>`或`<embed>`标签的附近（视觉范畴）插入补充文本
	- 为`<video>`和`<audio>`标签添加`<track>`
	
* 对于多媒体内容(`<embed>` `<object>` `<audio>` `<video>`)，自动通过软件转码，提供更多格式 __AAA__

- 链接改造
	* 如果`<a>`的`target`属性是`_blank`，改为`_self` __A__
	* 如果为站内链接，为`<a>`的`title`属性追加目标网页的标题 __AAA__
	* 如果为站内链接，为`<a>`的`title`属性追加"点击此链接将转出本网站"字样 __AA__
	* 为`<a>`标签增加`rev`和`rel`属性 __AAA__
	
* 根据网页的Id，应用代码级的替换规则 __AAA__
	
### 标准化

- 检测到不封闭的HTML时，在日志中留下警告 __AA__
- 封闭下列标签: __AA__
	* `<base>`
	* `<br>`
	* `<hr>`
	* `<img>`
	* `<option>`
	* `<embed>`
- 删除下列标签: __A__	
	* `<font>`
	* `<big>`
	* `<basefont>`
	* `<link>`
- 替换下列标签: __AA__	
	- `<big>` ~ `<span style="font-size:120%">`
	- `<center>` ~ `<p style="text-align:center">`
	- `<dir>` ~ `<ul>`
	- `<menu>`改成`<ul>`
	- `<div>`(如果内容空白) ~ `<br />`
	- `<tt>` ~ `<pre>`
	- `<marquee>` ~ `<p>`
	
- 检测长度超过20个字符的编码或某种语言，尝试设计通用算法插入`<wbr>`
- 检测长度超过20个字符的编码或某种语言，用`<data>`包裹，`value`属性就是自身

### 结构化和语义化

- 替换下列标签: __A__
	- `<i>` ~ `<em>`
	- `<b>` ~ `<strong>`
	- `<s>` ~ `<del>`
	- `<u>` ~ `<ins>`
- 尝试识别大标题并转成`<h1>` __AA__
- 尝试识别小标题并转成`<h2>..<h6>` __AAA__
- 尝试根据标题级为正文划分区域，包裹`<section>`标签 __AAA__
- 尝试识别列表，转成`<ul>`，不改变原有文本内容 __AAA__
- 将`<font>`尝试替换成`<strong> <h1> <h2> <mark>`等标签 __AAA__
- 尝试识别地址，使用`<address>`标签表示 __AAA__
- 尝试理解连续两个以上的`<br>`，并使用CSS的`margin`代替 __AAA__
- 尝试理解连续两个以上的`<p>`，并使用CSS的`margin`代替 __AAA__
- 尝试理解连续五个以上的空格，并使用CSS的`align`代替 __AAA__
- 尝试在上下文寻找**来源**之类的字眼，为`<blockquote>`和`q`补充`cite`属性 __AAA__
- 尝试把复杂的`<table>`重新用`<thead> <tbody> <tfoot> <thead>`构建 __AAA__
- 为正文添加`<article>`标签 __AA__
- 为具有`float:right`属性的文本添加`<aside>`标签 __AAA__
- 为时间和日期添加`<time>`标签 __AA__
- 为文章正文前的标题、摘要等包裹`<header>`标签 __AA__
- 为文章开头结尾版权、隐私、来源等声明包裹`<footer>`标签 __AA__
- 尝试理解黄色背景的`<span>`，用`<mark>`包裹 __AA__
- 尝试发现导航区域，用`<nav>`包裹 __AA__
- 发现与拼音有关的内容，用`<ruby>`描述 __AAA__
- 尝试发现涉及大量细节的文本，用`<detail>`和`<summary>`降低视觉混乱 __AAA__

## 断句

原始文本句子前后插入`<span id="<hash>" class="yz_sentence">..</span>`，根据句号、问号、感叹号、分号断句。

可选方案：使用HTML5 `<data>`标签。`value`属性就是文本的hash。

要求:

- 句子上限100字，否则在逗号断或者在第100字断 __A__
- 考虑Unicode，标点集合中包括所有语言的句号类型的标点 __AAA__
- 兼容中英文混合断句 __AA__

## 模块

### 日志

- 格式: [Time] [Type] [Column] [Message]
- 类型如下：
	- 信息 [Info]
	- 警告 [Warning]
	- 错误 [Error]
	- 调试 [Debug]
	
- 在同一栏目下，不重复纪录类似的事件 __AAA__

### 规则

#### 规则定义

参考`sed`的语法。增加如下指令，考虑以降低规则中的重复代码：

* 封闭标签
* 用x标签包裹
* 根据Id查找标签
* 增加属性
* 修改属性
* 调用外部函数

#### 规则存储

- 以网站为单位独立存储
- UTF-8编码的文本文件

#### 规则批处理

- 用于若干规则的批量执行
- 编辑规则的执行顺序
- UTF-8编码的文本文件，内容就是规则的文件名列表

## 参考文档

- [W3C School](http://www.w3schools.com/html/default.asp)
- [Semantic Web](http://www.w3.org/standards/semanticweb/)