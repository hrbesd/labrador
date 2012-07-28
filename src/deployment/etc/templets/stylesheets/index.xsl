<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex" />
				<link rel="stylesheet" rev="stylesheet" href="assets/css/style.css" type="text/css" media="screen" />
				<link rel="stylesheet" type="text/css" href="assets/css/base.css" />
				<link rel="stylesheet" type="text/css" title="standard" href="assets/css/standard.css" />
				<link rel="stylesheet" type="text/css" title="dark" href="assets/css/dark.css" />
				<link rel="stylesheet" type="text/css" title="high_contrast" href="assets/css/high_contrast.css" />
				<link href="assets/css/accessible.css" rel="stylesheet" />
				<script src="assets/js/jquery.js"></script>
				<script src="assets/js/md5.js"></script>
				<script src="assets/js/soapclient.js"></script>
				<script src="assets/js/accessible/toolbox.js"></script>
				<script src="assets/js/accessible/basic.js"></script>
				<script src="assets/js/accessible/action.js"></script>
				<script src="assets/js/accessible/speaker.js"></script>
				<script src="assets/js/accessible/storage.js"></script>
				<script src="assets/js/accessible/trans.js"></script>
				<script src="assets/js/accessible/keybinding.js"></script>
				<script src="assets/js/accessible/keybinding.config.js"></script>
				<script src="assets/js/accessible/ui.js"></script>
				<title><xsl:value-of select="website/info"/></title>
			</head>
			<body>	
				<div class="toolbar">
					<div class="tbitem item_1">
				    	<a href="#" id="theme_standard" title="正常模式" class="item_a"></a>
				    	<a href="#" id="theme_dark" title="黑夜模式" class="item_b"></a>
				    	<a href="#" id="theme_highcontrast" title="高对比模式" class="item_c"></a>
				    </div>
					<div class="tbitem item_2">
				    	<a href="#" id="text_in" title="放大字体" class="item_a"></a>
				    	<a href="#" id="text_out" title="缩小字体" class="item_c"></a>
				    </div>
					<div class="tbitem item_3">
				    	<a href="#" id="increase_width" title="增加页宽" class="item_a"></a>
				    	<a href="#" id="decrease_width" title="减少页宽" class="item_c"></a>
				    </div>
					<div class="tbitem item_4">
				    	<a href="#" id="line_height_in" title="增加行距" class="item_a"></a>
				    	<a href="#" id="line_height_out" title="减少行距" class="item_c"></a>
				    </div>
					<div class="tbitem item_5">
				    	<a href="#" id="toggle_magnifier" title="放大镜" class="item_a"></a>
				        <a href="#" id="guides" title="辅助线" class="item_b"></a>
				    	<a href="accessibility.html" title="无障碍说明" class="item_c"></a>
				    </div>
					<div class="tbitem item_6">
				    	<a href="#" title="翻转对比度" class="item_a on"></a>
				    	<a href="#" id="toggle_speaker" title="声音开关" class="item_b"></a>
				    </div>
				</div>
				<div class="fixed-bottom">
					<div class="magnifier">
						<p id="magnified"></p>
					</div>
			    </div>
			    <div class="mod_translate">
					<p></p>
					<span class="sign"></span>
				</div>
				<div id="main">
					<!-- Consider using a large image for back ground -->
					<div id="top_banner">
						<img src="assets/img/top_banner.jpg" />
					</div>
					<div id="content">
						<header>
							<h1><xsl:value-of select="website/info"/></h1>
						</header>
						<nav>
							<ul class="major_col">
								<xsl:for-each select="website/nodeList/indexNode">
								<li>
									<a>
										<xsl:attribute name="href">
											<xsl:value-of select="node/pageUrl"/>
										</xsl:attribute>
										<xsl:value-of select="node/name"/>
									</a>
									<ul class="sub_col">
										<xsl:for-each select="nodeList/node">
											<li>
												<a>
													<xsl:attribute name="href">
														<xsl:value-of select="pageUrl"/>
													</xsl:attribute>
													<xsl:value-of select="name" />
												</a>
											</li>
										</xsl:for-each>
									</ul>
								</li>
								</xsl:for-each>
							</ul>
						</nav>
					</div>
					<div id="foot">
						<footer>
							<p id="powered">
								运营支持： <a href="http://www.hrbesd.com/">哈尔滨e时代</a>
							</p>
							<ul id="footer_links">
								<li>
									<a href="about.html">关于本站</a>
								</li>
								<li>
									<a href="accessibility.html">信息无障碍说明</a>
								</li>
								<li>
									<a href="sitemap.html">站点地图</a>
								</li>
								<li>
									<a>
										<xsl:attribute name="href">
											<xsl:value-of select="website/url"/>
										</xsl:attribute>
										返回原始页面
									</a>
								</li>
							</ul>
						</footer>
					</div>
				</div>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
