<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex"/>
				<title><xsl:value-of select="column/name"/></title>
			</head>
			<body>
				<nav>
					<ul>
						<li><a href="../index.xml">首页</a></li>
						<li>
							<a href="#"><xsl:value-of select="column/name"/></a>
						</li>
					</ul>
				</nav>
				<header>
					<h1><xsl:value-of select="column/name"/></h1>
				</header>
				<!-- List of sub-columns -->
				<ul>
					<xsl:for-each select="column/nodeList/node">
						<li>
							<a>
								<xsl:attribute name="href">
									<xsl:value-of select="pageUrl"/>
								</xsl:attribute>
								<xsl:value-of select="name"/>
							</a>
						</li>
					</xsl:for-each>
				</ul>
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
									<xsl:value-of select="column/url"/>
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