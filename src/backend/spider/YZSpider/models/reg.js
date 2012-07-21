function getYZSpiderResult(content)
{
    var result = new Array();
	var startIndex = content.indexOf("<div class=\"slidingList_none\" id=\"slidingList2\" style=\"height:27px\">");
    var endIndex = content.indexOf("</div>",startIndex+1);
    var tmp = content.substring(startIndex,endIndex);
    var reg = new RegExp("<li> <a href=\"([^\"]*)\"","g");
    var regResult = reg.exec(tmp);
	while(reg.lastIndex!==0)
	{
		result.push(regResult[1]);
		regResult = reg.exec(tmp);
	}
    return result;
}