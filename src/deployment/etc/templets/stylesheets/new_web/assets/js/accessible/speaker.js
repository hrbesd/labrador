/**
 * 语音朗读模块
 *
 * 提供调用后端提供语音朗读部分的功能代码
 * “包”名： speaker
 *
 * Author: Void Main
 */
var speaker = {};

// 伪成员变量
speaker.url = "http://116.255.231.36:8083";
speaker.index=0;//连读索引
speaker.source = new Array();//连续缓存
speaker.speakerStatus=false;
speaker.batchStatus=false;
speaker.continueStatus=false;
speaker.audioPlaying = false;
speaker.read_enabled = true;
//载入通信和播放的flash
speaker.flashvars = { allowScriptAccess:"always"}; 
document.write("<div id=\"esd_voice_div\"></div>");
speaker.swf="assets/swf/httpService.swf";
swfobject.embedSWF(speaker.swf, "esd_voice_div", "0", "0",
                   "9.0.0", "expressInstall.swf",
                    speaker.flashvars,null, null, null);


function wsInit(){
	var obj = swfobject.getObjectById("esd_voice_div");
	if (obj) {
		speaker.ws = obj;
	}
}
//读完语音的回调函数
function playComplete(){
	speaker.index++;
	/*
	if(speaker.batchStatus==false){
		return;
	}
	*/
	if(speaker.index>(speaker.source.length-1)){
		speaker.index = 0;
		return;
	}
	speaker.batch.speak(speaker.index);
}
// 伪成员方法
function callback(data) {
	xmldoc=new JSXML();
	xmldoc.LoadXML(data);
	//var url = xmldoc.FirstChild;
	//var url = xmldoc.GetByName("audio");
	//var mp3url = xmldoc.GetValue(url);
	var XPath='url';  
    var xml= xmldoc.GetSingleNode(XPath);
    var mp3Url = xmldoc.GetValue(xml);
	if (speaker.ws) {
		speaker.ws.esdStart(mp3Url);
	}
 }
 //停止朗读
speaker.stop = function(){
	speaker.speakerStatus=false;
	speaker.batchStatus=false;
	speaker.index=0;
	if (speaker.ws) {
		speaker.ws.esdStop();
	}
}
//连读
speaker.batch={};
speaker.batch.speak = function(index){
	if(speaker.batchStatus==false){
		return;
	}
	//遍历保存数据
	$('span[class=tts_data]').each(function() {
	  	speaker.source.push(this.innerHTML);
    });
   speaker.speak(speaker.source[index]);
}
//点读
speaker.point={};
speaker.point.speak = function(text){
	if(speaker.speakerStatus==false){
		return;
	}
	speaker.speak(text)
}
speaker.toolbar={}
speaker.toolbar.speak=function(toolbar_id){
	var url = "assets/mp3/"+toolbar_id+".mp3"
	if (speaker.ws) {
	    //document.getElementById("myDiv").innerHTML = url;
		speaker.ws.esdStart(url);
	}
}
// 朗读方法，唯一的对外接口
speaker.speak = function (text)
{
    text = encodeURIComponent(text);
    //var targetUrl = speaker.url + "/TextToSpeech/webservice/text2Speech/text2Speech?key=zhangjianzong&text=" + text+"&base64=null";
    var targetUrl = speaker.url + "/TextToSpeech/webservice/text2Speech/getStatus?jobID=null&text=" + text;
	if (speaker.ws) {
		speaker.ws.load(targetUrl);
	}
}
