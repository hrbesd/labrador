#后端整体设计

##后端工作流程
后端的整体工作流程分为四个部分，spider，parser，reactor和assembler
###1. spider阶段
####输入
  输入[spider配置文件](https://github.com/zhf/labrador/blob/master/docs/backend/spider_config_spec.md)
####处理过程
  根据配置文件扫描XML规则，根据规则建立结构体，并通过规则递归的扩展结构体，直到没有后继规则为止，将所有的叶子节点（即正文节点）下载保存到本地
####输出
- 把抓取的正文节点通过MD5算法将URL映射为文件名进行本地存储，本地存储会按文件名的前两位来建立目录并进行管理。
- XML目录文件，用来描述网站的逻辑结构

###2. parser阶段
###3. reactor阶段
###4. assembler阶段

##后端文件存储方式
网站首页和目录文件的内容只在spider爬行节点使用，并不保存到本地文件系统。本地文件系统保存网页正文数据。每个网站建立一个文件夹，
每个文件夹下包含一个XML目录文件和spider，parser，reactor，assembler四个子文件夹，这四个子文件夹作为输出文件的保存路径。子文件夹内再通过文件名的前两位建立子文件夹。