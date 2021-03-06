function parseArticle(content,url) {
    var articleItem = { title: '', body: '', lastModified: '', author: '' , version: '0.1.0' , refreshTag:''};
    if(content.indexOf("http-equiv=\"refresh\"") != -1)
    {
    	articleItem.refreshTag="true";
    }
    else
    {
    	articleItem.refreshTag="false";
    }
    if (url.indexOf("system") != -1) {
        var authorStartIndex = content.indexOf("<!--function source");
        if (authorStartIndex != -1) {
            authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
            var authorEndIndex = content.indexOf("<", authorStartIndex);
            articleItem.author = content.substr(authorStartIndex, authorEndIndex - authorStartIndex);
        }

        var lastModifiedStartIndex =  content.lastIndexOf("parse_date=");
        if (lastModifiedStartIndex != -1) {
            lastModifiedStartIndex = content.indexOf("=", lastModifiedStartIndex) + 2;
            var lastModifiedEndIndex = content.indexOf("\"",  lastModifiedStartIndex+2);
            articleItem.lastModified = content.substr(lastModifiedStartIndex, lastModifiedEndIndex - lastModifiedStartIndex);
        }

        var bodyStartIndex = content.lastIndexOf("<!--function content() parse begin-->");
        if (bodyStartIndex != -1) {
            bodyStartIndex = content.indexOf(">", bodyStartIndex) + 1;
            var bodyEndIndex = content.indexOf("<!--function: content() parse end", bodyStartIndex);
            articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
        }
    }
    else if (url.indexOf("http://www.hlj.gov.cn/zjlj/") != -1) {
        var bodyStartIndex = content.indexOf("<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
        var bodyEndIndex = bodyStartIndex;
        var tableCount = 0;
        while (bodyEndIndex != -1) {
            var bodyEndIndex = content.indexOf("table", bodyEndIndex + 1);
            if (content[bodyEndIndex - 1] == "<") {
                tableCount = tableCount + 1;
            }
            else {
                tableCount = tableCount - 1;
            }
            if (tableCount == 0) {
                articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex + 6);
                break;
            }
        }
    }
    else if (url.indexOf("http://www.hlj.gov.cn/jgsz") != -1) {
        var bodyStartIndex = content.indexOf("<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"4\"  class=\"boxborder\">");
        var bodyEndIndex = bodyStartIndex;
        var tableCount = 0;
        while (bodyEndIndex != -1) {
            var bodyEndIndex = content.indexOf("table", bodyEndIndex + 1);
            if (content[bodyEndIndex - 1] == "<") {
                tableCount = tableCount + 1;
            }
            else {
                tableCount = tableCount - 1;
            }
            if (tableCount == 0) {
                articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex + 6);
                break;
            }

        }
    }
    else if (url.indexOf("http://www.hlj.gov.cn/zwdt/lddt/ldjs") != -1) {
        var bodyStartIndex = content.indexOf("<td valign=\"top\">") + 17;
        var bodyEndIndex = bodyStartIndex;
        var tableCount = 0;
        while (bodyEndIndex != -1) {
            var bodyEndIndex = content.indexOf("table", bodyEndIndex + 1);
            if (content[bodyEndIndex - 1] == "<") {
                tableCount = tableCount + 1;
            }
            else {
                tableCount = tableCount - 1;
            }
            if (tableCount == 0) {
                articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex + 6);
                break;
            }
        }
    }
    else if ((url.indexOf("http://www.hlj.gov.cn/cylj/cyfw/") != -1) || (url.indexOf("http://www.hlj.gov.cn/cylj/ljgw/") != -1))
    {
        var bodyStartIndex = content.indexOf("<table width=\"100%\" border=\"0\" cellspacing=\"1\"");
        var bodyEndIndex = bodyStartIndex;
        var tableCount = 0;
        while (bodyEndIndex != -1) {
            var bodyEndIndex = content.indexOf("table", bodyEndIndex + 1);
            if (content[bodyEndIndex - 1] == "<") {
                tableCount = tableCount + 1;
            }
            else {
                tableCount = tableCount - 1;
            }
            if (tableCount == 0) {
                articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex + 6);
                break;
            }
        }
    }
    else {

    }
    return articleItem;
}