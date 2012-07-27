<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/">
		<html>
			<head>
				<meta charset="utf-8"/>
				<meta name="robots" content="noindex"/>
				<link rel="stylesheet" type="text/css" href="../assets/css/base.css" />
				<title><xsl:value-of select="column/name"/></title>
			</head>
			<body>
				<div id="main">
					<!-- Location. e.g. Home > You > Are > Here -->
					<div id="loc">
						<nav>
							<ul>
								<xsl:for-each select="column/parentPageUrl/node">
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
									<a href="#"><xsl:value-of select="column/name"/></a>
								</li>
							</ul>
						</nav>
					</div>
					<div id="content">
						<header>
							<h1><xsl:value-of select="column/name"/></h1>
						</header>
						<!-- List of sub-columns -->
						<ul class="col">
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
											<xsl:value-of select="column/url"/>
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