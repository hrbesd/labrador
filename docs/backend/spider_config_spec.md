#爬虫配置文件设计文档

*作者：耿海龙*

*不完整*

*可用来指导实现*

##配置文件功能说明
	每个网站保存一个配置文件，Spider根据网站的配置文件进行爬行分析。

##配置文件操作说明
* 使用者：运营方
* 使用方法：	通过SpiderConfigGenerator工具生成配置文件
* 使用规则：
	运营方负责维护和构建网站的配置文件，网站的配置文件全部手动生成和修改，爬虫不会修改配置文件内容。
	
##配置文件设计说明
###整体设计说
配置文件中有手动规则和自动规则，nodeList保存所有手动添加的节点，Rule记录所有的动态规则。手动添加的nodelist节点和Rule记录匹配出来的节点一起构成spider的爬行范围。
### Rule规则说明
Rule目前包含两种规则，正则表达式和JavaScript脚本语言
#### 正则表达式
* 适用类型：适用于在网页中可以直接通过字符串匹配来找到目标信息的情况
* 编写规则：通过正则语言确定匹配范围，通过pattern（小括号的形式）实现精准的信息匹配，每个正则表达式中有且仅有一个模式，spider将直接从pattern中提取匹配结果。
* 额外参数：无

#### Javascript脚本
* 适用类型：
	- 很难用正则表达式确定范围
			
			例子:
				目标信息没有很强的特征，或者特征很难提取，使用正则表达式
			会匹配出多个结果，但只有其中的一部分结果是想要的。
	- 目标具有很强的规律性，可以通过循环直接产生目标信息
	
			例子:
				如Url的值为: www.xxx.com/aa/001.html
				            …
				            www.xxx.com/aa/999.html
				则可以通过Javascript代码直接生成目标信息
	- 信息并没有明文显示出来，是通过javascript代码动态生成的
	
			例子:
				http://www.beijing.gov.cn/sy/rdgz/中的下一页是
			通过Javascript代码动态生成的，直接的字符串匹配方法无法
			获得结果。
	- 内容是用过Ajax动态从服务器上获取的
	
			例子：
				一些动态内容可能并没有直接下载到本地，是通过Ajax动态
			获取的，因此需要我们模拟网站的行为去服务器获取内容。          
* 编写规则
		
			规则示例：
				function getYZSpiderResult() 
				{
					var result = new Array();
					…………
					blah, blah, blah……
					do anything you want :)
					…………
					return result;
				}
* 参数
 	* executeOnlyOnce
 		- 类型：bool （true，false）
 		- 说明：
 				
 				如果为true，则脚本运行一次之后就会被清除
 				如果为false，则脚本被保留，每次都会被执行
 		- 示例：
 					
 				例子：
 					1. 生成list页面的所有正文链接地址，则每个list页面只需运
 				行一次就可以获得该页面的所有链接地址，此时executeOnlyOnce
 				为true。 
 				   2. 还没遇到，相信会遇到的 :)
 				

##数据结构定义
<pre><code>

struct Expression
{
    String type;         //value type: {RegExp, JavaScript}
    String executeOnlyOnce;     //execute only once flag : {true,false}
    String label;     // used as key
    String value;     // used as value
};

struct Rule
{
    List<Expression> expressionList;
    Expression nextPageExpression;
    Expression urlExpression;
    Expression titleExpression;
    String maxPageCount;
    List<Node> nodeList;
    Rule* childRule;
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
                &lt;expressionList&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value=""/&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value=""/&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value=""/&gt;
                &lt;/expressionList&gt;
                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                &lt;childRule/&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;zhengfugonggao&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm#&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;ruleList&gt;
                            &lt;rule&gt;
                                &lt;expressionList&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value=""/&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value="&lt;a .*href=&quot;([^&quot;]*)&quot; class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; onmouseout=&quot;this.className='bgc1'"/&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value="class=&quot;bgc1&quot; onmouseover=&quot;this.className='bgc2'&quot; .*&lt;span&gt;(.*)&lt;/span&gt;"/&gt;
                                &lt;/expressionList&gt;
                                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                &lt;childRule&gt;
                                    &lt;rule&gt;
                                        &lt;expressionList&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value="&lt;a href=&quot;([^&quot;]*)&quot; class=&quot;Next&quot;&gt;下页"/&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value="&lt;a class=&quot;f3348&quot; href=&quot;([^&quot;]*)&quot;"/&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value="&lt;a class=&quot;f3348&quot;.*title=&quot;([^&quot;]*)&quot;"/&gt;
                                        &lt;/expressionList&gt;
                                        &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
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
                &lt;expressionList&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value=""/&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value=""/&gt;
                    &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value=""/&gt;
                &lt;/expressionList&gt;
                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                &lt;childRule/&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;bumendongtai&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/bmdt.htm&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;ruleList&gt;
                            &lt;rule&gt;
                                &lt;expressionList&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value=""/&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value="&lt;a .*href=&quot;([^&quot;]*)&quot; class=&quot;hei14&quot;&gt;"/&gt;
                                    &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value="&lt;FONT class=&quot;hei12&quot;&gt;(.*)&lt;/font&gt;"/&gt;
                                &lt;/expressionList&gt;
                                &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
                                &lt;childRule&gt;
                                    &lt;rule&gt;
                                        &lt;expressionList&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="nextPage" value="&lt;a href=&quot;([^&quot;]*)&quot; class=&quot;Next&quot;&gt;下页"/&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="url" value=" &lt;a class=&quot;f3665&quot; href=&quot;([^&quot;]*)&quot;"/&gt;
                                            &lt;expression type="RegExp" executeOnlyOnce="false" label="title" value="class=&quot;f3665&quot; title=&quot;([^&quot;]*)&quot;"/&gt;
                                        &lt;/expressionList&gt;
                                        &lt;maxPageCount&gt;&lt;/maxPageCount&gt;
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


  