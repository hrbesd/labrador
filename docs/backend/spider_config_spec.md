#爬虫配置文件设计文档

*作者：耿海龙*

##配置文件说明
每个网站保存一个配置文件，Spider根据网站的配置文件进行爬行分析。运营方负责维护和构建网站的配置文件，
网站的配置文件全部手动生成和修改，爬虫不会修改配置文件。配置文件中有手动规则和自动规则，nodeList保存所有手动添加的节点，Rule记录所有的动态规则。
正则表达式负责自动获取节点信息，手动添加的节点和自动添加的节点合并为最后要分析的节点。后期会为配置文件生成器开发图形界面。
##数据结构定义
<pre><code>
struct Rule
{
    String urlRegExp;
    String nextPageRegExp;
    String maxPageCount;
    String nameRegExp;
    Rule*   childRule;
    List<Node> nodeList;
};

struct Node
{
    String url;
    String name;
    String refreshRate;
    List<Rule*> ruleList;
};

struct WebSite
{
    Node node;
    String info;
    String editor;
    String crawlTime;
    String threadLimit;
};
</code></pre>

##数据属性说明
Website结构负责保存整个网站的信息，Node用来递归的定义栏目的描述信息,Rule用来定义向下扩展的规则

- WebSite描述一个网站的整体信息

    * info: 网站的描述信息
    * editor： 网站配置文件编辑者
    * node: 记录网站的链接信息
	* crawlTime: 爬行时间
	* threadLimit： 最大线程数

- Node 描述一个页面的信息
    * url: 页面的url地址
    * name： 页面的名称
    * refreshRate： 记录页面刷新
    * ruleList： 页面匹配规则列表

- Rule 记录匹配规则
    * urlRegExp： 匹配页面链接的正则表达式
    * nextPageRegExp： 用来找出下一页地址的正则表达式
    * maxPageCount： 记录最多翻页数
    * nameRegExp： 用来匹配链接标题的正则表达式
    * nodeList： 用来手工添加子栏目节点
    * childRule： 应用于下层节点的规则

##XML示例
	
分析[中国哈尔滨](http://www.harbin.gov.cn/)的政府公告栏目和部门动态栏目

<pre><code>
&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;website&gt;
    &lt;editor&gt;genghailong&lt;/editor&gt;
    &lt;info&gt;zhong guo haerbin&lt;/info&gt;
    &lt;crawlTime&gt;&lt;/crawlTime&gt;
    &lt;threadLimit&gt;10&lt;/threadLimit&gt;
    &lt;node&gt;
        &lt;name&gt;chinese harbin&lt;/name&gt;
        &lt;url&gt;http://www.harbin.gov.cn/&lt;/url&gt;
        &lt;refreshRate&gt;&lt;/refreshRate&gt;
        &lt;ruleList&gt;
            &lt;rule&gt;
                &lt;urlRegExp&gt;&lt;/urlRegExp&gt;
                &lt;nextPageRegExp&gt;&lt;/nextPageRegExp&gt;
                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                &lt;nameRegExp&gt;&lt;/nameRegExp&gt;
                &lt;childRule/&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;zhengfugonggao&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm#&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;ruleList&gt;
                            &lt;rule&gt;
                                &lt;urlRegExp&gt;&lt;a .*href=&quot;([^&quot;]*)&quot; class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; onmouseout=&quot;this.className='bgc1'&lt;/urlRegExp&gt;
                                &lt;nextPageRegExp&gt;&lt;/nextPageRegExp&gt;
                                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                &lt;nameRegExp&gt;class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; .*&lt;span&gt;(.*)&lt;/span&gt;&lt;/nameRegExp&gt;
                                &lt;childRule&gt;
                                    &lt;rule&gt;
                                        &lt;urlRegExp&gt;&lt;a class=&quot;f3348&quot; href=&quot;([^&quot;]*)&quot;&lt;/urlRegExp&gt;
                                        &lt;nextPageRegExp&gt;&lt;a href=&quot;([^&quot;]*)&quot; class=&quot;Next&quot;&gt;下页&lt;/nextPageRegExp&gt;
                                        &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                        &lt;nameRegExp&gt;&lt;a class=&quot;f3348&quot;.*title=&quot;([^&quot;]*)&quot;&lt;/nameRegExp&gt;
                                        &lt;childRule/&gt;
                                        &lt;nodeList/&gt;
                                    &lt;/rule&gt;
                                &lt;/childRule&gt;
                                &lt;nodeList/&gt;
                            &lt;/rule&gt;
                        &lt;/ruleList&gt;
                    &lt;/node&gt;
                &lt;/nodeList&gt;
            &lt;/rule&gt;
            &lt;rule&gt;
                &lt;urlRegExp&gt;&lt;/urlRegExp&gt;
                &lt;nextPageRegExp&gt;&lt;/nextPageRegExp&gt;
                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                &lt;nameRegExp&gt;&lt;/nameRegExp&gt;
                &lt;childRule/&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;bumendongtai&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/bmdt.htm&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;ruleList&gt;
                            &lt;rule&gt;
                                &lt;urlRegExp&gt;&lt;a .*href=&quot;([^&quot;]*)&quot; class=&quot;hei14&quot;&gt;&lt;/urlRegExp&gt;
                                &lt;nextPageRegExp&gt;&lt;/nextPageRegExp&gt;
                                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                &lt;nameRegExp&gt;&lt;FONT class=&quot;hei12&quot;&gt;(.*)&lt;/font&gt;&lt;/nameRegExp&gt;
                                &lt;childRule&gt;
                                    &lt;rule&gt;
                                        &lt;urlRegExp&gt; &lt;a class=&quot;f3665&quot; href=&quot;([^&quot;]*)&quot;&lt;/urlRegExp&gt;
                                        &lt;nextPageRegExp&gt;&lt;a href=&quot;([^&quot;]*)&quot; class=&quot;Next&quot;&gt;下页&lt;/nextPageRegExp&gt;
                                        &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                        &lt;nameRegExp&gt;class=&quot;f3665&quot; title=&quot;([^&quot;]*)&quot;&lt;/nameRegExp&gt;
                                        &lt;childRule/&gt;
                                        &lt;nodeList/&gt;
                                    &lt;/rule&gt;
                                &lt;/childRule&gt;
                                &lt;nodeList/&gt;
                            &lt;/rule&gt;
                        &lt;/ruleList&gt;
                    &lt;/node&gt;
                &lt;/nodeList&gt;
            &lt;/rule&gt;
        &lt;/ruleList&gt;
    &lt;/node&gt;
&lt;/website&gt;
</code></pre>

##已知问题和解决办法

- 父栏目与子栏目URL相同，无法爬行子栏目
	* 例子：中国哈尔滨[政府公告](http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm), 栏目URL与子栏目URL一样
	* 产生问题的原因： 在爬行的过程中为了避免出现环状URL无法跳出，或者多个页面链向同一个页面造成多次访问同一页面资源浪费，在本地保存了已访问的URL集合，如果URL已经被访问过就直接跳过。所以如果子栏目和父栏目有同样的URL就无法进入子栏目链接并应用子栏目的规则
	* 解决办法： 在父栏目URL后面加入#（页内定位符）来与子栏目URL进行区分


  