# Spider 技术说明书

*不完整*

*可用来指导实现*

#模块说明
Spider模块负责从网站收集信息，根据网站的逻辑层次分析网站并建立目录结构，下载网页的正文并将结果传递给Parser模块做进一步处理

#接口说明
- 输入
	* [Spider配置文件](https://github.com/zhf/labrador/blob/master/docs/backend/spider_config_spec.md)
- 输出
	* XML目录文件
		* 命名方式： Spider配置文件中Website节点的Node节点的Name属性+下划线+dir.xml。 如chinese harbin_dir.xml
		* 存储格式： 
			* 文法规则
				<pre>
					struct Node
					{
					    String url;
					    String name;
					    String refreshRate;
						String hashName;
					    List<Node> nodeList;
					};

					struct WebSite
					{
					    Node node;
					    String info;
					    String editor;
					};
				</pre>
			* 示例
			<pre><code>
			&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;website&gt;
    &lt;editor&gt;genghailong&lt;/editor&gt;
    &lt;info&gt;zhong guo haerbin&lt;/info&gt;
    &lt;node&gt;
        &lt;name&gt;chinese harbin&lt;/name&gt;
        &lt;url&gt;http://www.harbin.gov.cn/&lt;/url&gt;
        &lt;refreshRate&gt;&lt;/refreshRate&gt;
        &lt;hashName&gt;&lt;/hashName&gt;
        &lt;nodeList&gt;
            &lt;node&gt;
                &lt;name&gt;zhengfugonggao&lt;/name&gt;
                &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm&lt;/url&gt;
                &lt;refreshRate&gt;&lt;/refreshRate&gt;
                &lt;hashName&gt;&lt;/hashName&gt;
                &lt;nodeList&gt;
                    &lt;node&gt;
                        &lt;name&gt;2012年政府公告&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2012.htm&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;hashName&gt;&lt;/hashName&gt;
                        &lt;nodeList/&gt;
                    &lt;/node&gt;
                    &lt;node&gt;
                        &lt;name&gt;2011年政府公告&lt;/name&gt;
                        &lt;url&gt;http://www.harbin.gov.cn/zwxxgk/zfgg/zfgg2011.htm&lt;/url&gt;
                        &lt;refreshRate&gt;&lt;/refreshRate&gt;
                        &lt;hashName&gt;&lt;/hashName&gt;
                        &lt;nodeList&gt;
                            &lt;node&gt;
                                &lt;name&gt;关于清理整顿临街商服违章广告牌匾的通告&lt;/name&gt;
                                &lt;url&gt;http://www.harbin.gov.cn/info/news/index/detail/236379.htm&lt;/url&gt;
                                &lt;refreshRate&gt;&lt;/refreshRate&gt;
                                &lt;hashName&gt;04902ded1831095bf0a52e1123017c0e&lt;/hashName&gt;
                            &lt;/node&gt;
                            &lt;node&gt;
                                &lt;name&gt;关于清理取缔擅自占用城市道路设置商亭通告&lt;/name&gt;
                                &lt;url&gt;http://www.harbin.gov.cn/info/news/index/detail/236378.htm&lt;/url&gt;
                                &lt;refreshRate&gt;&lt;/refreshRate&gt;
                                &lt;hashName&gt;8ca276688ee780162e0212e6d59b2691&lt;/hashName&gt;
                            &lt;/node&gt;
  			&lt;/nodeList&gt;
                    &lt;/node&gt;
                &lt;/nodeList&gt;
            &lt;/node&gt;
        &lt;/nodeList&gt;
    &lt;/node&gt;
&lt;/website&gt;

			</pre></code>

	