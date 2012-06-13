#爬虫配置文件设计文档

*作者：耿海龙*

##配置文件说明
每个网站保存一个配置文件，Spider根据网站的配置文件进行爬行分析。运营方负责维护和构建网站的配置文件，
网站的配置文件全部手动生成和修改，爬虫不会修改配置文件。配置文件中有手动规则和自动规则，nodeList保存所有手动添加的节点，
正则表达式负责自动获取节点信息，手动添加的节点和自动添加的节点合并为最后要分析的节点。后期会为配置文件生成器开发图形界面。
##数据结构定义
<pre><code>
struct Node
{
    String url;
    String name;
    String urlRegExp;
    String nextPageRegExp;
    String maxPageCount;
    String refreshRate;
    String nameRegExp;
    List<Node> nodeList;
};

struct WebSite
{
    String url;
    String urlRegExp;
    String nameRegExp;
    String name;
    List<Node> nodeList;
};
</code></pre>
##数据属性说明
Website结构负责保存整个网站的信息，Node用来递归的定义栏目的描述信息
###WebSite
    url: 网站的URL地址
    name： 网站名称
    urlRegExp: 用来自动匹配栏目url的正则表达式
    nameRegExp: 用来自动匹配栏目名称的正则表达式
    nodeList: 用来手工添加栏目节点信息
###Node
    url: 栏目的url地址
    name： 栏目的名称
    urlRegExp： 匹配子栏目或者正文URL的正则表达式
    nextPageRegExp： 用来找出下一页地址的正则表达式
    maxPageCount： 记录最多翻页数
    refreshRate： 记录刷新率
    nameRegExp： 用来匹配子栏目标题或正文标题的正则表达式
    nodeList： 用来手工添加子栏目节点
##XML示例
    <?xml version="1.0" encoding="UTF-8"?>
    <website>
    <name>chinese harbin</name>
    <urlRegExp></urlRegExp>
    <url>http://www.harbin.gov.cn/</url>
    <nameRegExp></nameRegExp>
    <NodeList>
        <name>zhengfugonggao</name>
        <url>http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm</url>
        <urlRegExp>&lt;a .*href=&quot;([^&quot;]*)&quot; class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; onmouseout=&quot;this.className='bgc1'</urlRegExp>
        <nextPageRegExp></nextPageRegExp>
        <maxPageCount></maxPageCount>
        <refreshRate></refreshRate>
        <nameRegExp>class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; .*&lt;span&gt;(.*)&lt;/span&gt;</nameRegExp>
        <NodeList>
            <name></name>
            <url></url>
            <urlRegExp>&lt;a class=&quot;f3348&quot; href=&quot;([^&quot;]*)&quot;</urlRegExp>
            <nextPageRegExp>&lt;a href=&quot;([^&quot;]*)&quot; class=&quot;Next&quot;&gt;下页</nextPageRegExp>
            <maxPageCount></maxPageCount>
            <refreshRate></refreshRate>
            <nameRegExp>&lt;a class=&quot;f3348&quot;.*title=&quot;([^&quot;]*)&quot;</nameRegExp>
            <NodeList/>
        </NodeList>
    </NodeList>
    </website>

  