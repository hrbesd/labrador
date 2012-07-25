function getYZSpiderResult(content)
{
    var result = new Array();
	var bodyStartIndex = content.lastIndexOf("<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
    if (bodyStartIndex != -1) {
        bodyStartIndex = content.indexOf(">", bodyStartIndex) + 1;
        var bodyEndIndex = content.indexOf("<table width=\"980\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\">", bodyStartIndex);
        var body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex);
    }
	result.push(body);
    return result;
}

