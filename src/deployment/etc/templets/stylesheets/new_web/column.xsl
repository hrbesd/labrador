<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
  <xsl:template match="/">
<html>
<head>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<meta name="robots" content="noindex, nofollow" />
		<!-- Order does matter -->
		<link href="../assets/css/base.css" rel="stylesheet" type="text/css" />
		<link href="../assets/css/accessible.css" rel="stylesheet" type="text/css" />
		<link href="../assets/css/toolbar.css" rel="stylesheet" type="text/css" />
		<link href="../assets/css/jquery-bubble-popup-v3.css" rel="stylesheet" type="text/css" />

		<link rel="stylesheet" type="text/css" title="highcontrast" href="../assets/css/highcontrast.css" />
<!--
		<link rel="stylesheet" type="text/css" title="standard" 	href="assets/css/standard.css" />
		<link rel="stylesheet" type="text/css" title="dark" 		href="assets/css/dark.css" />
-->

		<script type="text/javascript" src="../assets/js/jquery.js"></script>
		<script type="text/javascript" src="../assets/js/jquery-bubble-popup-v3.min.js"></script>
		<script type="text/javascript" src="../assets/js/md5.js"></script>
		<script type="text/javascript" src="../assets/js/soapclient.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/speaker.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/storage.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/keybinding.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/keybinding.config.js"></script>


		<!-- 语音需要加载的js start-->
		<script type="text/javascript" src="../assets/script/soundmanager2.js"></script>
    	<script type="text/javascript" src="../assets/js/accessible/JSXML.js"></script>
    	<script type="text/javascript" src="../assets/js/accessible/swfobject.js"></script>
    	<script type="text/javascript" src="../assets/js/accessible/speaker.js"></script>
    	<!-- 语音需要加载的js end-->
		<script type="text/javascript" src="../assets/js/accessible/basic.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/action.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/toolbox.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/trans.js"></script>
		<script type="text/javascript" src="../assets/js/accessible/text.js"></script>
		<title><xsl:value-of select="column/name"/></title>
</head>
<body>
<div id="toolbar" class="clearfix">
<section>
	<div class="btn_group item_11">
		<a href="#" id="theme_standard" 	title="正常模式" 	class="item_a"></a>
		<a href="#" id="theme_dark" 		title="黑夜模式" 	class="item_b"></a>
		<a href="#" id="theme_highcontrast" title="高对比模式" 	class="item_c"></a>
	</div>
	<div class="btn_group item_31">
		<a href="#" id="text_in" 			title="放大字体" 	class="item_a"></a>
		<a href="#" id="reset_text" 		title="复位字体" 	class="item_b"></a>
		<a href="#" id="text_out" 			title="缩小字体" 	class="item_c"></a>
	</div>
	<div class="btn_group item_41">
		<a href="#" id="increase_width" 	title="增加页宽" 	class="item_a"></a>
		<a href="#" id="reset_width" 		title="复位页宽" 	class="item_b"></a>
		<a href="#" id="decrease_width" 	title="减少页宽" 	class="item_c"></a>
	</div>
	<div class="btn_group item_51">
		<a href="#" id="line_height_in" 	title="增加行距" 	class="item_a"></a>
		<a href="#" id="line_height_reset" 	title="复位行距" 	class="item_b"></a>
		<a href="#" id="line_height_out" 	title="减少行距" 	class="item_c"></a>
	</div>
	<div class="btn_group item_71">
		<a href="#" id="reset_page" 		title="复位页面" 	class="item_a"></a>
		<a href="#" id="toggle_speaker" 	title="声音开关" 	class="item_b"></a>
		<a href="#" id="toggle_translate" 	title="翻译开关" 	class="item_c"></a>
	</div>
	<div class="btn_group item_61">
		<a href="#" id="toggle_magnifier" 	title="放大镜" 		class="item_a"></a>
		<a href="#" id="guides" 			title="辅助线" 		class="item_b"></a>
		<a href="accessibility.html" 		title="无障碍说明" 	class="item_c"></a>
	</div>
</section>
</div>
<div id="main">
	<header>
	<div class="banner">
		<img src="../assets/img/top_banner.jpg" alt="网站横幅"/>
	</div>
	<nav>
	<ul class="loc">
		<xsl:for-each select="column/parentpageurl/node">
      <li>
        <a>
          <xsl:attribute name="href">
            <xsl:value-of select="pageurl"/>
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
		<xsl:for-each select="column/nodelist/node [position() &lt; 1000]">
      <li>
        <a>
          <xsl:attribute name="href">
            <xsl:value-of select="pageurl"/>
          </xsl:attribute>
          <xsl:attribute name="class">column-entrance</xsl:attribute>
          <xsl:copy-of select="name"/>
        </a>
      </li>
    </xsl:for-each>
	</ul>
</div>
<div>
	<footer>
	<ul id="footer_links">
		<li>
			<a href="../about.html">关于本站</a>
		</li>
		<li>
			<a href="../accessibility.html">无障碍说明</a>
		</li>
		<li>
			<a href="../browsers.html">浏览器支持</a>
		</li>
		<li>
			<a>
        <xsl:attribute name="href">
          <xsl:value-of select="column/url"/>
        </xsl:attribute>
        返回原始页面
      </a>
		</li>
	</ul>
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