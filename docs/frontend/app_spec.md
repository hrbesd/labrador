# 移动版App技术文档

*不完整*

*可以用来指导实现*

## 目的

实现Feature Spec中关于`移动App`的部分。目前产品设计以支持使用触摸屏的智能手机为主。

## 支持平台

* iOS __A__
* Android __A__
* Windows Phone __AA__

## 接口

* 主页和栏目模板与Assembler共享接口（Web Service）
* 为主页的一级栏目额外提供图标接口 __A__
* 为植入广告/链接留下接口 __AA__
* 为给用户发信息留下接口 __AA__

## 开发人员

* 程序员1名
* 美工1名
* 程序经理1名 (解释需求，协调接口)

## 特性

### 移动版App展现出独有的功能或界面

* 利用App全屏幕的优势，模拟书本、活页夹等现实物品，直观地展现信息 __AA__
* 如果可以使用平台的TTS，不使用云端的TTS服务 __AA__
* 尝试获得设备信息，以确保默认字体大小适应屏幕 __AA__
* 如果平台支持，提供正文内的语音搜索功能 __AAA__
* 屏幕转动后，调整栏目布局 __AA__
* 屏幕转动后，调整正文中图片和视频的布局 __AAA__
* 为上下左右滑动赋予功能 __AA__
* 为多点触摸赋予功能 __AAA__
* 提供反转对比度的快捷方式 __A__
* 提供快捷方式，以牺牲美观为代价，切换到一种高对比度的户外模式 __AA__
* 提供全站文本离线浏览 __AAA__
* 允许用户使用浏览器打开当前文章 __AA__
* 提供（社交）分享功能 __AA__
* 利用Native App能够访问设备的优势，提供额外增值功能 __AAA__

## 界面设计

### 主页

* 欢迎性的Splash（程序加载时） __A__
* 进站语音 __A__
* 短暂动画（可取自客户的宣传片） __AAA__
* 以`Icon View`展示一级栏目 __A__
* 选择图标进入子栏目有动画效果 __AAA__

### 子栏目

* 嵌入浏览器控件或者使用`ListView`之类的控件 __A__
* 使用非标准控件时，响应缩放等手势出发的事件 __AA__
* 有快捷的方式返回到上一级 __A__
* 用户可以调整栏目顺序，在本机记忆 __AAA__
* 平等的栏目列表使用两种不同背景色交替渲染 __AA__
* 可以分组的栏目列表以不同背景颜色表示 __AAA__
* 选择栏目，由栏目进入文章有动画效果 __AAA__



### 文章列表

* 嵌入浏览器控件或者使用`ListView`之类的控件 __A__
* 有快捷的方式返回到上一级 __A__
* 使用非标准控件时，响应缩放等手势出发的事件 __AA__
* 如果屏幕受限，有操作和不离开当前列表的前提下提供关于作者和时间的信息 __AAA__



### 正文

* 嵌入浏览器控件 __A__
* 隐藏地址栏等无关界面 __A__
* 如果数据源的正文是分页的，提供便捷翻页功能 __AA__
* 翻页伴有动画效果 __AAA__
* 为组图设计缩略图功能，操作方式符合平台的图片管理软件的习惯 __AAA__
* 为音乐、视频之类的内容单独设计界面和操作方式 __AAA__


## 开发周期

* 利用模板缩短开发周期 __AA__
* 利用模板、设置和脚本，让运营方自动生成App __AAA__

## 辅助功能

* 符合平台的Accessible规范 __A__
* 如果需要，实现辅助功能接口 __AA__

## 提交

* 因为提交可能需要审核时间，所以尽量把需要常更新的内容留给Web Service
* 软件尽量少使用权限

## 参考
* [Making Applications Accessible (Android)](https://developer.android.com/guide/topics/ui/accessibility/apps.html)

* [Making Your iPhone Application Accessible](https://developer.apple.com/library/ios/#documentation/UserExperience/Conceptual/iPhoneAccessibility/Making_Application_Accessible/Making_Application_Accessible.html#//apple_ref/doc/uid/TP40008785-CH102-SW5)