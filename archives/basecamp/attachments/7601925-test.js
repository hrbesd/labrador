function parseArticle(content) {
    var articleItem = { title: '', body: '', lastModified: '', author: '' }
    var authorStartIndex = content.indexOf("detail_ly");
    if (authorStartIndex != -1) {
        authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
        var authorEndIndex = content.indexOf("<", authorStartIndex);
        articleItem.author = content.substr(authorStartIndex, authorEndIndex - authorStartIndex);
    }

    var bodyStartIndex = content.lastIndexOf("detail_zw");
    bodyStartIndex = content.indexOf("<div", bodyStartIndex);
    var bodyEndIndex = content.indexOf("</div>", bodyStartIndex) + 6;
    articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    if (articleItem.body == "\n") {
        bodyStartIndex = content.lastIndexOf("<div id=\"zoom\" class=\"detail_zw\" align=\"left\">");
        bodyEndIndex = content.indexOf("</div>", bodyStartIndex) + 6
        articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    }
    
    return articleItem;
}