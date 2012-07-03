function parseArticle(content) {
    var articleItem = { title: '', body: '', lastModified: '', author: '' }
    var authorStartIndex = content.indexOf("À´Ô´£º");
    if (authorStartIndex != -1) {
        authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
        var authorEndIndex = content.indexOf("<", authorStartIndex);
        articleItem.author = content.substr(authorStartIndex, authorEndIndex - authorStartIndex);
    }
    else {
        authorStartIndex = content.indexOf("<td height=\"30\" align=\"center\" valign=\"top\" style=\"border-bottom:2px #C1C1C1 solid;padding-top:5px;\">");
        if (authorStartIndex != -1) {
            authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
            authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
            var authorEndIndex = content.indexOf("<", authorStartIndex);
            articleItem.author = content.substr(authorStartIndex, authorEndIndex - authorStartIndex);
        }
    }


    var bodyStartIndex = content.lastIndexOf("articlecontent");
    if (bodyStartIndex != -1) {
	    bodyStartIndex = content.indexOf(">", bodyStartIndex)+1;
	    var bodyEndIndex = content.indexOf("</div>", bodyStartIndex);
        articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    }
    else {
        bodyStartIndex = content.lastIndexOf("<td height=\"30\" align=\"center\" valign=\"top\" style=\"border-bottom:2px #C1C1C1 solid;padding-top:5px;\">");
        bodyStartIndex = content.indexOf("<tr>", bodyStartIndex);
        var bodyEndIndex = content.indexOf("<td align=\"center\" valign=\"top\"><script language=\"javascript\">", bodyStartIndex);
        articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    }
    return articleItem;
}