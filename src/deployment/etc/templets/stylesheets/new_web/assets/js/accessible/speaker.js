
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
speaker.index = 0;//连读索引
speaker.source = new Array();//连续缓存
//speaker.speakerStatus = false;
//speaker.batchStatus = false;
speaker.continueStatus = false;
speaker.audioPlaying = false;
speaker.read_enabled = true;
//载入通信和播放的flash
/*
speaker.flashvars = { allowScriptAccess:"always"}; 
document.write("<div id="esd_voice_div"></div>");
speaker.swf="assets/swf/httpService.swf";
swfobject.embedSWF(speaker.swf, "esd_voice_div", "0", "0",
                   "9.0.0", "expressInstall.swf",
                    speaker.flashvars,null, null, null);
*/
function wsInit() {
	var obj = swfobject.getObjectById("esd_voice_div");
	if (obj) {
		speaker.ws = obj;
	}
}
//读完语音的回调函数
function playComplete() {
	if(speaker.toolbar.flg.speak == true){
		speaker.toolbar.flg.speak=false;
		return;
	}
	$(speaker.source[speaker.index]).removeClass("tts_reading");
	speaker.index++;
	if (speaker.index > (speaker.source.length - 1)) {
		speaker.index = 0;
		return;
	}

	speaker.batch.speak(speaker.index);
}
// 伪成员方法
function callback(data) {
	xmldoc = new JSXML();
	xmldoc.LoadXML(data);
	//var url = xmldoc.FirstChild;
	//var url = xmldoc.GetByName("audio");
	//var mp3url = xmldoc.GetValue(url);
	var XPath = "url";
	var xml = xmldoc.GetSingleNode(XPath);
	var mp3Url = xmldoc.GetValue(xml);
	if (speaker.ws) {
		speaker.ws.esdStart(mp3Url);
	}
}
 //停止朗读
speaker.stop = function () {
	$(speaker.source[speaker.index]).removeClass("tts_reading");
	speaker.index = 0;
	if (speaker.ws) {
		speaker.ws.esdStop();
	}
};
//连读
speaker.batch = {};
speaker.batch.intervalId;
speaker.loadBatchRead = function(){
	var batch_read = storage.getCookie('batch_read');
    if(batch_read=='open'){
		speaker.batchStatus = true;
		$('#batch_read').addClass('on');
		storage.setCookie("batch_read",'open',360);
		speaker.batch.intervalId = setInterval(function(){
			if(speaker.ws){
				speaker.index=0;
				speaker.batch.speak(speaker.index);
				clearInterval(speaker.batch.intervalId);
			}
		}, 1000);
		//speaker.index=0;
		//speaker.batch.speak(speaker.index);
    }else{
		speaker.batchStatus = false;
		storage.setCookie("batch_read",'close',360);
		$('#batch_read').removeClass('on');
    }
  
}
speaker.batchRead = function(){
	if(speaker.batchStatus==false){
		speaker.batchStatus=true;
		storage.setCookie("batch_read",'open',360);
		$('#batch_read').addClass('on');
	}else{
		speaker.batchStatus=false;
		storage.setCookie("batch_read",'close',360);
		$('#batch_read').removeClass('on');
	}
   setTimeout(function(){
		speaker.index=0;
		speaker.batch.speak(speaker.index);
   },3000);
   
}
speaker.batch.speak = function (index) {
	if (speaker.batchStatus == false) {
		return;
	}
	//遍历保存数据
	$("span[class=tts_data]").each(function () {
		speaker.source.push(this);
	});
	$(speaker.source[index]).addClass("tts_reading");
	$(speaker.source[index]).parents('a').focus();
	speaker.speak(speaker.source[index].innerHTML);
};
//点读
speaker.point = {};
speaker.loadPointRead = function(){
	var point_read = storage.getCookie('point_read');
    if(point_read=='open'){
		speaker.speakerStatus = true;
		storage.setCookie("point_read",'open',360);
		$('#point_read').addClass('on');
    }else{
		speaker.speakerStatus = false;
		storage.setCookie("point_read",'close',360);
		$('#point_read').removeClass('on');
    }
   
}
speaker.pointRead = function(){
	if(speaker.speakerStatus==false){
		speaker.speakerStatus = true;
		storage.setCookie("point_read",'open',360);
		$('#point_read').addClass('on');
	}else{
		speaker.speakerStatus = false
		storage.setCookie("point_read",'close',360);
		$('#point_read').removeClass('on');
	}
}
speaker.point.speak = function (text) {
	if (speaker.speakerStatus == false) {
		return;
	}
	speaker.speak(text);
};
speaker.toolbar = {};
speaker.toolbar.speak = function (toolbar_id) {
	var url = "assets/mp3/" + toolbar_id + ".mp3";
	if (speaker.ws) {
	    //document.getElementById("myDiv").innerHTML = url;
		speaker.ws.esdStart(url);
	}
};
speaker.toolbar.flg={};
speaker.toolbar.click = function (toolbar_id) {
	//自动朗读
	if (toolbar_id == "batch_read") {
		if (speaker.batchStatus==false) {
			speaker.stop();
			speaker.toolbar.flg.speak = true;
			toolbar_id = toolbar_id + "_un";
		}
	}
	//即指即读
	if (toolbar_id == "point_read") {
		if (speaker.speakerStatus==false) {
			toolbar_id = toolbar_id + "_un";
		}
	}
	//翻译
	if (toolbar_id == "toggle_translate") {
		if (basic.translator.status==false) {
			toolbar_id = toolbar_id + "_un";
		}
	}
	//放大镜
	if (toolbar_id == "toggle_magnifier") {
		var magnifier = storage.getCookie('magnifier');
		if(magnifier=='hide'){
			toolbar_id = toolbar_id + "_un";
		}
	}
	//辅助线guides
	if (toolbar_id == "guides") {
		var guides = storage.getCookie('guides');
		if(guides=='hide'){
			toolbar_id = toolbar_id + "_un";
		}
	}


	var tool_url = "assets/mp3/click/" + toolbar_id + "_click.mp3";
	if (speaker.ws) {
		//document.getElementById("myDiv").innerHTML = tool_url;
		speaker.ws.esdStart(tool_url);
	}
};
// 朗读方法，唯一的对外接口
speaker.speak = function (text) {
	text = encodeURIComponent(text);
    //var targetUrl = speaker.url + "/TextToSpeech/webservice/text2Speech/text2Speech?key=zhangjianzong&text=" + text+"&base64=null";
	var targetUrl = speaker.url + "/TextToSpeech/webservice/text2Speech/getStatus?jobID=null&text=" + text;
	if (speaker.ws) {
		speaker.ws.load(targetUrl);
	}
};

