function getYZSpiderResult(content)
{
    var result = new Array();
	var bodyStartIndex = content.indexOf("<td valign=\"top\">")+17;
	var bodyEndIndex = bodyStartIndex;
	var tableCount = 0;
    while (bodyEndIndex != -1) {
        var bodyEndIndex = content.indexOf("table", bodyEndIndex+1);
		if(content[bodyEndIndex-1]=="<")
		{
			tableCount=tableCount+1;
		}
		else
		{
			tableCount=tableCount-1;
		}
		if(tableCount==0)
		{
			var body = content.substr(bodyStartIndex, bodyEndIndex - bodyStartIndex+6);
			break;
		}
    }
	result.push(body);
    return result;
}
