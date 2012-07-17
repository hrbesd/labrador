# Assembler测试用例

*指导模块测试*

*不涉及模块内部用例*

*不设计恶意测试用例*

## 测试目的

验证Assembler模块与Reactor模块整合是否顺利，是否能够生成正确输出

- Assembler前一个模块是Reactor
- 测试主要验证Reactor模块能否正常工作与结束，是否可以正确读取前一个模块的输入数据，生成的结果是否包含必要的元素，是否能够正常运行与显示

## 用例设计

- Reactor模块输入数据验证
	* 验证待处理网站根目录是否包含```workers```文件夹
	* 验证```workers```目录下是否有```reactor```文件夹
	* 验证```reactor```目录下是否全部为由两个字符组成的文件夹，例如```00```
	* 验证```reactor```的子文件夹中是否全部是文件名长度为32个字符（不包括文件扩展名，文件名由0-9，a-z组成），并且结尾为```.xml```的文件
	* 验证```.xml```文件中格式是否正确，是否包含```title```，```url```，```author```，```lastModified```，和```bodyData```几个节点
	
- Assembler工作验证
	* 验证```Assembler```模块是否正常退出，即模块执行完成之后，是否退出到命令行
	* 验证```Assembler```模块没有错误结束，验证最终的命令行输出是否包含```Error```或者```Exception```字样

- Assembler模块输出验证
	* 验证```workers```目录中是否有```assembler```目录，是否有```webroot```目录
	* 验证```assembler```目录中是否包含```index.xml```文件```a```目录，```c```目录，```l```目录，以及```xml_stylesheets```目录
	* 验证```index.xml```文件是否能够正常打开*
	* 验证```index.xml```文件头部是否包含类似```<?xml-stylesheet type="text/xsl" href="./xml_stylesheets/index.xsl"?>```的语句
	* 验证```index.xml```文件内容是否包含```website```节点，并且```website```节点是否包含```name```，```info```，```url```，```nodeList```节点
	* 验证```index.xml```文件中```nodeList```的子节点是否全部都是```node```节点，验证```node```节点的子节点是否包含```name```，```url```和```pageUrl```节点
	* 验证```xml_stylesheets```目录中的内容是否全部都是以```.xsl```结尾
	* 验证```xml_stylesheets```目录中的文件内容与```labrador```文件夹下```etc/templates/stylesheets```文件夹中的文件结构和内容一致
	* 验证```xml_stylesheets```目录中是否至少包含```article.xsl```，```index.xsl```，```column.xsl```和```list.xsl```几个文件
	* 验证```c```和```l```子目录中的文件全部是文件名长度为32个字符（不包括文件扩展名，文件名由0-9，a-z组成），并且结尾为```.xml```的文件
	* 验证```c```目录下的```.xml```文件头部是否包含类似```<?xml-stylesheet type="text/xsl" href="../xml_stylesheets/column.xsl"?>```的语句
	* 验证```c```目录下的```.xml```文件内容是否包括```column```父节点，验证父节点是否包含```name```，```url```，```parentPageUrl```和```nodeList```子节点
	* 验证```c```目录下的```.xml```文件的```parentPageUrl```节点的子节点是否全部都是```node```节点，这些```node```节点包括```name```和```pageUrl```子节点
	* 验证```c```目录下的```.xml```文件的```nodeList```节点的子节点是否全部都是```node```节点，这些```node```节点包括```name```，```url```和```pageUrl```子节点
	* 验证```l```目录下的```.xml```文件头部是否包含类似```<?xml-stylesheet type="text/xsl" href="../xml_stylesheets/list.xsl"?>```的语句
	* 验证```l```目录下的```.xml```文件内容是否包括```column```父节点，验证父节点是否包含```name```，```url```，```parentPageUrl```和```nodeList```子节点
	* 验证```l```目录下的```.xml```文件的```parentPageUrl```节点的子节点是否全部都是```node```节点，这些```node```节点包括```name```和```pageUrl```子节点
	* 验证```l```目录下的```.xml```文件的```nodeList```节点的子节点是否全部都是```node```节点，这些```node```节点包括```name```，```url```和```pageUrl```子节点
	* 验证```a```目录中是否全部为由两个字符组成的文件夹，例如```00```
	* 验证```a```的子文件夹中是否全部是文件名长度为32个字符（不包括文件扩展名，文件名由0-9，a-z组成），并且结尾为```.xml```的文件
	* 验证```a```目录下的```.xml```文件头部是否包含类似```<?xml-stylesheet type="text/xsl" href="../xml_stylesheets/article.xsl"?>```的语句
	* 验证```.xml```文件中格式是否正确，父节点是否为```article```节点，父	节点是否包含```title```，```url```，```author```，```lastModified```，和```bodyData```几个子节点
	* 验证```webroot```目录内容与```assembler```目录结构完全一致
	* 验证通过外网能否访问生成的页面
	* 验证生成的界面表现是否与设计结果一致
	* 验证生成的页面之间跳转是否正常，是否有死链接
	* 验证工具箱功能是否正常