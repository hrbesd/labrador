<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"
  encoding="utf-8" doctype-system="about:legacy-compat" />
  <xsl:template match="/">
<html>
<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<meta name="robots" content="noindex, nofollow" />
		<!-- Order does matter -->
    <link href="/assets/css/base.css" rel="stylesheet" type="text/css" />
    <link href="/assets/css/accessible.css" rel="stylesheet" type="text/css" />
    <link href="/assets/css/toolbar.css" rel="stylesheet" type="text/css" />
    <link href="/assets/css/jquery-bubble-popup-v3.css" rel="stylesheet" type="text/css" />
    <link rel="stylesheet" type="text/css" title="standard"   href="/assets/css/standard.css" />
<!--
    <link rel="stylesheet" type="text/css" title="highcontrast" href="/assets/css/highcontrast.css" />
    <link rel="stylesheet" type="text/css" title="dark"     href="/assets/css/dark.css" />
-->
      <!-- 通用的js -->
    <script type="text/javascript" src="/assets/js/jquery.js"></script>
	<!-- 加载jQuery1.3.2版本 -->
 	<script type="text/javascript" src="/assets/js/jquery-1.3.2.min.js"></script>
	<script type="text/javascript"> var jQuery_1_3_2 = $.noConflict(true);</script>
    <script type="text/javascript" src="/assets/js/jquery-bubble-popup-v3.min.js"></script>
    <!--添加soundmanager2 支持 和 bas64编码-->
    <script type="text/javascript" src="/assets/js/soundmanager2-nodebug-jsmin.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/base64.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/basic.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/action.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/storage.js"></script>
    <!-- 语音加载的2个js -->
      <script type="text/javascript" src="/assets/js/accessible/speaker.js"></script>
      <!-- 工具栏 -->
    <script type="text/javascript" src="/assets/js/accessible/toolbox.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/text.js"></script>
    <!-- 快捷键绑定用的3个js -->
    <script type="text/javascript" src="/assets/js/accessible/keybinding.js"></script>
    <script type="text/javascript" src="/assets/js/accessible/keybinding.config.js"></script>

      <!-- 翻译功能的1个js-->
    <script type="text/javascript" src="/assets/js/accessible/trans.js"></script>

	<title><xsl:value-of select="column/ptitle"/></title>				
</head>
<body>
<div id="toolbar" class="clearfix">
    <section>
      <div class="btn_group item_11">
        <a href="#" id="theme_standard"   title="正常模式"  class="item_a"></a>
        <a href="#" id="theme_dark"     title="黑夜模式"  class="item_b"></a>
        <a href="#" id="theme_highcontrast" title="高对比模式"   class="item_c"></a>
      </div>
      <div class="btn_group item_21">
        <a href="#" id="text_in"      title="放大字体"  class="item_a"></a>
        <a href="#" id="reset_text"     title="复位字体"  class="item_b"></a>
        <a href="#" id="text_out"       title="缩小字体"  class="item_c"></a>
      </div>
      <div class="btn_group item_31">
        <a href="#" id="increase_width"   title="增加页宽"  class="item_a"></a>
        <a href="#" id="reset_width"    title="复位页宽"  class="item_b"></a>
        <a href="#" id="decrease_width"   title="减少页宽"  class="item_c"></a>
      </div>
      <div class="btn_group item_41">
        <a href="#" id="line_height_in"   title="增加行距"  class="item_a"></a>
        <a href="#" id="line_height_reset"  title="复位行距"  class="item_b"></a>
        <a href="#" id="line_height_out"  title="减少行距"  class="item_c"></a>
      </div>
      <div id="dynamicIcon" class="btn_group item_61_000">
        <a href="#" id="batch_read"     title="自动朗读"  class="item_a"></a>
        <a href="#" id="point_read"     title="即指即读"  class="item_b"></a>
        <a href="#" id="toggle_translate"   title="翻译/Translator"   class="item_c"></a>
      </div>
      <div class="btn_group item_71">
        <a href="#" id="toggle_magnifier"   title="放大镜"     class="item_a"></a>
        <a href="#" id="guides"       title="辅助线"     class="item_b"></a>
        <a href="../accessible.xml" id="accessibility"     title="无障碍说明"   class="item_c"></a>
      </div>
    </section>
    </div>
<div id="main">
	<header>
	<div class="banner">
		<img src="../assets/custom/top_banner.jpg" alt="网站横幅"/>
	</div>
	<nav>
	<ul class="loc">
		<xsl:for-each select="column/parentpageurl/node">
      <li>
        <a>
          <xsl:attribute name="href">
            <xsl:value-of select="pageurl"/>
          </xsl:attribute>
              <xsl:attribute name="title">
                <xsl:value-of select="name"/>
              </xsl:attribute> 
          <xsl:copy-of select="name"/>
        </a>
      </li>
    </xsl:for-each>
	</ul>
	</nav>
	</header>
	<header>
	<h1><xsl:copy-of select="column/name"/></h1>
	</header>
	<ul class="column clearfix">
		<xsl:for-each select="column/nodelist/node">
      <xsl:sort data-type="number" select="level" />
      <xsl:if test="position() &lt; 1001">
      <li>
        <a>
          <xsl:attribute name="href">
            <xsl:value-of select="pageurl"/>
          </xsl:attribute>
              <xsl:attribute name="title">
                <xsl:value-of select="name"/>
              </xsl:attribute> 
         <xsl:attribute name="class">column-entrance</xsl:attribute>
          <xsl:copy-of select="name"/>
        </a>
      </li>
      </xsl:if>
    </xsl:for-each>
	</ul>
</div>
<div>
	<footer>
	<ul id="footer_links">
		<li>
			<a href="../about.xml"><span class="tts_data">关于本站</span></a>
		</li>
		<li>
			<a href="../accessible.xml"><span class="tts_data">无障碍说明</span></a>
		</li>
		<li>
			<a href="../browsers.xml"><span class="tts_data">浏览器支持</span></a>
		</li>
		<li>
			<a>
        <xsl:attribute name="href">
          <xsl:value-of select="normalize-space(column/url)"/></xsl:attribute>
        <span class="tts_data">返回原始页面</span>
      </a>
		</li>
	</ul>
        <ul id="footer_links"><li><a href="http://www.hrbesd.com"><span class="tts_data">无障碍云技术支持单位：哈尔滨亿时代数码科技开发有限公司</span></a></li></ul>
</footer>
</div>
<div class="magnifier">
	<div class="screen">
		<div>
			<span></span>
		</div>
	</div>
</div>
</body>
</html>
  </xsl:template>
</xsl:stylesheet>
