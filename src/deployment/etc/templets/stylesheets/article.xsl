<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex"/>
				<link rel="stylesheet" type="text/css" href="../../assets/css/base.css" />
				<title><xsl:value-of select="article/title"/></title>
			</head>
			<body>
				<div id="main">
					<!-- Location. e.g. Home > You > Are > Here -->
					<div id="loc">
						<nav>
							<ul>
								<xsl:for-each select="article/parentpageurl/node">
									<li>
										<a>
											<xsl:attribute name="href">
												<xsl:value-of select="pageurl"/>
											</xsl:attribute>
											<xsl:value-of select="name"/>
										</a>
									</li>
								</xsl:for-each>
								<li>
									<a href="#"><xsl:value-of select="article/title"/></a>
								</li>
							</ul>
						</nav>
					</div>
					<div id="content">
						<article>
							<header>
								<h1><xsl:value-of select="article/title"/></h1>
								<span id="author"><xsl:value-of select="article/author"/></span>
								<span id="pubdate"><xsl:value-of select="article/lastmodified"/></span>
							</header>
							<section>
								<xsl:copy-of select="article/bodydata"/>
							</section>
						</article>
					</div>
					<div id="foot">
						<footer>
							<p id="powered">
								Powered by <a href="http://www.hrbesd.com/">ESD</a>
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
											<xsl:value-of select="artical/url"/>
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
