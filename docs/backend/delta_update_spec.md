#Delta Update说明文档

##简要介绍
Delta Update就是通过增量的方式对数据进行更新，只处理新增的数据，从而加快处理速度，减少网络流量，进而减少运行成本。

##优点
* 每次只处理新增的文档，所以处理的数据量会变得很小，处理的速度会加快，网络带宽占用会变少。
* 增量的方式有利于任务分解，将一个大的任务分成多个增量，从而有利于并发执行
* 增量有利于将各个模块之间流水作业，可以实现多个模块异步处理。

##设计规则
1. 最小操作单位为一个正文文件
2. 模块之间通过x文件进行通信和数据同步
3. 每个x文件的结构完全相同
4. x文件由递增序号命名（以创建时间为序号？）

##数据结构

###主要数据结构说明
* x文件：x文件记录了网站的逻辑结构，即网站栏目与栏目之间如何链接，栏目下包含哪些列表，列表又包含哪些正文。
* 数据文件：数据文件即包含正文的网页文件。命名格式为对原始文件名进行hash运算之后的64位数字名称，他们存储在很多小文件夹中，这些小文件夹由hash名字的前两位命名。

###主要数据结构定义
1. x数据格式
	* 数据格式定义
	<pre><code>
	struct Node
	{
   		String url;		//url of webpage
    	String name; 	//title of webpage
   		String hashName;  //hash name of url
	 	List&lt;Node&gt; nodeList; //nodelist of children nodes
	 	Type type;  // operation type. [add,update,remove]
	};
		struct WebSite
	{
        Node node;		//the index page 
    	String info;   //website information
    	String editor;   //who edit this file
	};
	</code></pre>
	* 数据格式举例
	<pre><code>
	&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;website&gt;
    &lt;editor&gt;genghailong&lt;/editor&gt;
    &lt;info&gt;zhong guo haerbin&lt;/info&gt;
    &lt;node&gt;
        &lt;name&gt;chinese harbin&lt;/name&gt;
        &lt;url&gt;http://www.harbin.gov.cn/&lt;/url&gt;
        &lt;type&gt;add&lt;/type&gt;
        &lt;hashName&gt;e31258c2c3dd45d4256a577fc7d5b55a&lt;/hashName&gt;
        &lt;nodeList&gt;
            &lt;node&gt;
                &lt;name&gt;zhengfugonggao&lt;/name&gt;
                &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm#&lt;/url&gt;
                &lt;type&gt;add&lt;/type&gt;
                &lt;hashName&gt;2ab18cb69487ddc2cea2417be9ff0865&lt;/hashName&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;2012年政府公告&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm&lt;/url&gt;
                        &lt;type&gt;add&lt;/type&gt;
                        &lt;hashName&gt;4edf9336373c858be50c0f35cdd5a2a5&lt;/hashName&gt;
                        &lt;nodeList&gt;
                            &lt;node&gt;
                                &lt;name&gt;哈尔滨电业局关于部分线路停电的通知 &lt;/name&gt;
                                &lt;url&gt;http://www.harbin.gov.cn/info/news/index/detail/318904.htm&lt;/url&gt;
                                &lt;type&gt;add&lt;/type&gt;
                                &lt;hashName&gt;5b56522727af88520ede8aa93bb4f918&lt;/hashName&gt;
                            &lt;/node&gt;
                            &lt;node&gt;
                                &lt;name&gt;南岗区“两沟”综合整治项目征收安置居民进户通知&lt;/name&gt;
                                &lt;url&gt;http://www.harbin.gov.cn/info/news/index/detail/318823.htm&lt;/url&gt;
                                &lt;type&gt;add&lt;/type&gt;
                                &lt;hashName&gt;54e506a6218b1398caebeaa679857377&lt;/hashName&gt;
                            &lt;/node&gt;
	</code></pre>

##处理流程
###spider模块
注意：网站配置文件永远不动，最近更新的x文件只读方式读取，只修改新建x文件

1. 加载spider网站配置文件，建立规则系统，确定扫描范围。
2. spider尝试加载上一个x文件（即最近更新的x文件）。
3. 如果没有这个最新x文件，则新建一个x文件初始化，初始化的x文件中所有元素都将是add类型，x文件内容为规则匹配出来的所有文件。
4. 如果有这个最新x文件，则根据规则分析每个栏目最新的lastmodified时间，对比网站栏目上的正文更新时间，将最新更新时间比当前x记录中更新的文件记录到一个新建的x文件中，将这些文件节点的类型设为add。如果出现了lastmodified时间为空的文件，则比较网页标题，将目录上比x文件中第一个文件之后出现的文章近路到新x文件中，并标记为add。
5. 新的x文件将不包含上个x文件的内容，但要保证每个栏目至少有一个文件节点，用来记录最新文件的更新记录。
6. spider输出新的x文件，并将新的x文件传递给parser
7. spider开始在后台下载网页（漫长的过程）

###parser模块
1. parser模块以只读方式加载新x文件，并对x文件中的正文网页进行分析，将结果输出到worker/parser文件夹

###reactor模块

###assembler模块
1. assembler模块先加载上一次的目录索引文件，建立网站拓扑结构图
2. assembler根据新x文件对网站结构拓扑图进行增删改。
3. assembler生成新的目录索引文件，并更新webroot
