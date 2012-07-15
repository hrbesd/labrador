<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex"/>
				<title><xsl:value-of select="article/title"/></title>
			</head>
			<body>
				<nav>
					<ul>
						<xsl:for-each select="article/parentPageUrl/node">
							<li>
								<a>
									<xsl:attribute name="href">
										<xsl:value-of select="pageUrl"/>
									</xsl:attribute>
									<xsl:value-of select="name"/>
								</a>
							</li>
						</xsl:for-each>
						<li>
							<a href="#"><xsl:value-of select="article/name"/></a>
						</li>
					</ul>
				</nav>
				<article>
					<header>
						<h1><xsl:value-of select="article/title"/></h1>
						<p><xsl:value-of select="article/author"/></p>
						<p><xsl:value-of select="article/lastmodified"/></p>
					</header>
					<section>
						<xsl:value-of select="article/bodydata"/>
					</section>
				</article>
				<footer>
					<ul>
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
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
