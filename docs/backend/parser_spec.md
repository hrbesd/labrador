#解析器技术文档

##功能
解析器负责从网页正文中提取标题，作者，正文，URL，最后修改时间等元素，删除其他无用元素，将最终结果保存为XML文档，供reactor调用。
此外在分析正文时，解析器要记录原来的分页位置，为后续模块处理提供方便。

##设计方案

###输入
- spider生成的目录文件
- spider下载的正文文件
- parser解析规则文件

###输出
- 处理后的正文XML文件

###算法逻辑

####处理正文多页显示
    将每个原始网页正文用<page num="1"> ... </page>闭合标签标记，方便后续处理
