# Spider测试用例

*指导模块测试*

*不涉及模块内部用例*

*不设计恶意测试用例*

## 测试目的

验证Spider模块与后续模块的整合是否顺利，是否能够产生预期输出

- Spider的后续模块是Parser
- 测试主要验证Spider模块能否正常工作与结束，能否为下一个模块提供输出数据

## 用例设计

- Spider配置文件验证
	* 验证待处理网站根目录是否包含```workers```文件夹
	* 验证待处理网站根目录是否包含```rules```文件夹
	* 验证```rules```文件夹中是否包含```spider```文件夹，且```spider```文件夹下包含 ```spider_config.xml```文件
	* 验证```spider_config.xml```文件是否合法，是否为空

- Spider工作验证
	* 验证```Spider```模块是否正常退出，即模块执行完成之后，是否退出到命令行
		1. 验证```Spider```模块是否输出```Spider start to run…```
		2. 验证```Spider```模块是否输出网页下载信息，形式为```数字+web page downloaded```
		3. 验证```Spider```模块是否输出```finish download webpages```信息

- Spider模块输出结构验证
	* 验证```workers```目录下是否有```spider```文件夹
		* 验证```spider```目录下是否全部为由两个字符组成的文件夹，例如```00```
		* 验证```spider```文件夹的子文件夹中是否全部是文件名长度为32个字符（无文件扩展名，文件名由0-9，a-z组成）的文件，并验证这些文件是否为空
	* 验证```workers```目录下是否有```shared```文件夹
		* 验证shared文件夹下是否包含一个名字为```网站名+_dir.xml```的xml文件，并验证其非空，该文件为网站的目录树
	* 验证```logs```目录下是否包含```spider.log```文件