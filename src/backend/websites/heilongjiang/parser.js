function parseArticle(content) {
    var articleItem = { title: '', body: '', lastModified: '', author: '' }
    var authorStartIndex = content.indexOf("<!--function source");
    if (authorStartIndex != -1) {
        authorStartIndex = content.indexOf(">", authorStartIndex) + 1;
        var authorEndIndex = content.indexOf("<", authorStartIndex);
        articleItem.author = content.substr(authorStartIndex, authorEndIndex - authorStartIndex);
    }

    var bodyStartIndex = content.lastIndexOf("<!--function content() parse begin-->");
    if (bodyStartIndex != -1) {
        bodyStartIndex = content.indexOf(">", bodyStartIndex) + 1;
        var bodyEndIndex = content.indexOf("<!--function: content() parse end", bodyStartIndex);
        articleItem.body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    }
    return articleItem;
}