<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
  <xsl:template match="/">
    <html xmlns="http://www.w3.org/1999/xhtml">
      <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="robots" content="noindex" />
        <!-- Stylesheets -->
        <link rel="stylesheet" type="text/css" title="standard" href="../../assets/css/standard.css" />
        <link rel="stylesheet" type="text/css" title="dark" href="../../assets/css/dark.css" />
        <link rel="stylesheet" type="text/css" title="high_contrast" href="../../assets/css/highcontrast.css" />
        <link href="../../assets/css/accessible.css" rel="stylesheet" />
        <!-- JavaScript -->
        <script type="text/javascript" src="../../assets/js/jquery.js"></script>
        <script type="text/javascript" src="../../assets/js/md5.js"></script>
        <script type="text/javascript" src="../../assets/js/soapclient.js"></script>
        <script type="text/javascript" src="../../assets/script/soundmanager2.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/toolbox.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/basic.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/action.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/speaker.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/storage.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/trans.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/keybinding.js"></script>
        <script type="text/javascript" src="../../assets/js/accessible/keybinding.config.js"></script>
        <title><xsl:value-of select="article/title"/></title>
      </head>

      <body>
        <div id="xory" class="top-x">
          <div class="toolbar1 ">
            <div class="tbitem1 item_11">
              <a href="#" id="theme_standard" title="正常模式" class="item_a"></a>
              <a href="#" id="theme_dark" title="黑夜模式" class="item_b"></a>
              <a href="#" id="theme_highcontrast" title="高对比模式" class="item_c"></a>
            </div>
            <div class="tbitem1 item_31">
              <a href="#" id="text_in" title="放大字体" class="item_a"></a>
              <a href="#" id="text_out" title="缩小字体" class="item_c"></a>
            </div>
            <div class="tbitem1 item_41">
              <a href="#" id="increase_width" title="增加页宽" class="item_a"></a>
              <a href="#" id="decrease_width" title="减少页宽" class="item_c"></a>
            </div>
            <div class="tbitem1 item_51">
              <a href="#" id="line_height_in" title="增加行距" class="item_a"></a>
              <a href="#" id="line_height_out" title="减少行距" class="item_c"></a>
            </div>
            <div class="tbitem1 item_61">
              <a href="#" id="toggle_magnifier" title="放大镜" class="item_a"></a>
              <a href="#" id="guides" title="辅助线" class="item_b"></a>
              <a href="accessibility.html" title="无障碍说明" class="item_c"></a>
            </div>
            <div class="tbitem1 item_71">
              <a href="#" id="switch_hori_vert" title="横竖切换" class="item_a"></a>
              <a href="#" id="toggle_speaker" title="声音开关" class="item_b"></a>
              <a href="#" id="toggle_translate" title="翻译开关" class="item_c"></a>
            </div>
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
          <!--banner-->
          <div class="main-ti">
            <img src="../../assets/img/top_banner.jpg" />
          </div><!--banner end-->

          <nav>
            <ul class="nav-main">
              <xsl:for-each select="article/parentpageurl/node">
                <li>
                  <a>
                    <xsl:attribute name="href">
                      <xsl:value-of select="pageurl"/>
                    </xsl:attribute>
                    <xsl:copy-of select="name"/>
                  </a>
                </li>
                <li><b>></b></li>
              </xsl:for-each>
              <li>
                <a href="#"><xsl:copy-of select="article/title"/></a>
              </li>
            </ul>
          </nav>

          <article>
      			<header>
              <h1 class="title1">
                <p><xsl:copy-of select="article/title"/></p>
                <p><xsl:copy-of select="article/author"/></p>
                <p><xsl:copy-of select="article/lastmodified"/></p>
              </h1>
            </header>
      			<section>
        			<div class="section1">
                <xsl:copy-of select="article/bodydata/*" />
        			</div>
    			  </section>
    		  </article>
        </div>
        <footer>
          <div class="footer">
            <ul class="footerc">
              <li><a href="../../about.html">关于本站</a></li>
              <li><a href="../../accessibility.html">无障碍说明</a></li>
              <li><a href="../../browsers.html">浏览器支持</a></li>
              <li>
              <a>
                <xsl:attribute name="href">
                  <xsl:value-of select="article/url"/>
                </xsl:attribute>
                返回原始页面
              </a>
              </li>
            </ul>
          </div>
        </footer>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
