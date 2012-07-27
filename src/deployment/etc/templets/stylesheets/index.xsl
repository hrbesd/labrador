<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex" />
				<link rel="stylesheet" type="text/css" href="assets/css/base.css" />
				<title><xsl:value-of select="website/info"/></title>
			</head>
			<body>
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
								<xsl:for-each select="website/nodeList/node">
								<li>
									<a>
										<xsl:attribute name="href">
											<xsl:value-of select="pageUrl"/>
										</xsl:attribute>
										<xsl:value-of select="name"/>
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
