#webrootGenerator模块说明

*不完整*

*可用来指导实现*

##目的
根据网站XML目录文件生成webroot骨架结构，建立目录与目录，目录与正文之间的导航关系

##如何使用
由assembler调用，并将结果返回给assembler

##对不同平台的输出结果进行优化
在webrootGenerator之前，所有的数据都是完整的，统一的。
webrootGenerator根据assembler传入的配置文件针对不同平台进行优化，如将目录切分，对目录大小进行限制，因为该配置文件assembler其他部分也要用，所以由assembler模块来统一设计。

##接口
- 输入
 * --index-file ：网站XML目录文件的地址
 * --webroot-dir ：存放临时webroot的文件夹
 * --log-file ：log文件的输出地址 默认为程序所在目录
 * --version ：向标准输出输出版本信息
- 输出
 * webroot文件夹
     * 根目录index.xml文件，网站的入口
     * c文件夹负责存放栏目目录，栏目的下级节点是栏目或者列表
     * l文件夹负责存放列表文件，列表文件的下级节点是正文文件
     * a文件夹存放正文文件，因为没有reactor的输出结果，所以只填充了导航信息

##后续工作
1. 控制webroot的内存占用，通过边读取XML，边建树，边分析，边释放，控制内存使用量
2. 通过读取assembler传入的配置文件对目录大小进行限制，包括删除多余节点，将目录进行切分，按序号进行排列，提供上一页和下一页功能


