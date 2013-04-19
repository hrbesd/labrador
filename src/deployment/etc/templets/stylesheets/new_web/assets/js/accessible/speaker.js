/**
 * 语音朗读模块
 *
 * 提供调用后端提供语音朗读部分的功能代码
 * “包”名： speaker
 *
 * Author: snailzhang
 */
var speaker = {};

// 伪成员变量
speaker.url = "http://voice.yunmd.net";
speaker.index = 0;//连读索引
speaker.source = new Array();//连续缓存

 //停止朗读
speaker.stop = function () {
	$(speaker.source[speaker.index]).removeClass("tts_reading");
	speaker.index = 0;
	if (speaker.ws) {
		speaker.mp3Object.destruct();
	}
};
//自动朗读========================================================================================
speaker.batch = {};
speaker.batch.intervalId;
//通过cookie初始化
speaker.loadBatchRead = function(){
	var batch_read = storage.getCookie('batch_read');
    	if(batch_read=='open'){
			speaker.batchStatus = true;
			$('#batch_read').addClass('on');
			storage.setCookie("batch_read",'open',360);
			speaker.index=0;
			speaker.batch.speak(speaker.index);
    	}else{
			speaker.batchStatus = false;
			storage.setCookie("batch_read",'close',360);
			$('#batch_read').removeClass('on');
    	}
  
}
speaker.batch.esdStart = function(url){
	if(speaker.batch.mp3Object!=null){
		speaker.batch.mp3Object.destruct();
	}
	speaker.batch.mp3Object= soundManager.createSound({
                id:'batch',
                url:url,
                onfinish:batchcallback
        });
      speaker.batch.mp3Object.play();
}
function batchcallback(){
	if(speaker.batch.mp3Object!=null){
		speaker.batch.mp3Object.destruct();
	}
	playComplete();
}
//连读需要调用的方法
function playComplete() {
	$(speaker.source[speaker.index]).removeClass("tts_reading");
	speaker.index++;
	if (speaker.index > (speaker.source.length - 1)) {
		speaker.index = 0;
	}
	speaker.batch.speak(speaker.index);
}
//通过页面按钮操作
speaker.batchRead = function(){
	//无论开启和关闭都先清除正在朗读的语音
	if(speaker.batch.mp3Object!=null){
		speaker.batch.mp3Object.destruct();
	}
	if(speaker.batchStatus==false){//关闭状态转为开启
		speaker.batchStatus=true;
		storage.setCookie("batch_read",'open',360);
		$('#batch_read').addClass('on');
		basic.dynamicIcon.change("batch_read");
		speaker.batch.intervalId=setTimeout(function(){
			speaker.index=0;
			speaker.batch.speak();
		 },2000);
	}else{
		window.clearTimeout(speaker.batch.intervalId);
		speaker.batchStatus=false;
		storage.setCookie("batch_read",'close',360);
		$('#batch_read').removeClass('on');
		basic.dynamicIcon.change("batch_read");
		$(speaker.source[speaker.index]).removeClass("tts_reading");
	}
   
}
speaker.batch.speak = function () {
	if (speaker.batchStatus == false) {
		return;
	}
	//遍历保存数据
	$("span[class=tts_data]").each(function () {
		speaker.source.push(this);
	});
	$(speaker.source[speaker.index]).addClass("tts_reading");
	$(speaker.source[speaker.index]).parents('a').focus();
	var text = speaker.source[speaker.index].innerHTML;
	var de= base64.e64(text);
   	$.ajax({
		type:'GET',
		url:speaker.url+'/ws/t2s',
		dataType:'jsonp',
		jsonp:"callback",
		data:{"b":de},
		async: true,
		success:function(data){
		    speaker.batch.esdStart(data.u);
		}
   	})
	
};
//即指即读=================================================================================================
speaker.point = {};
speaker.point.esdStart = function(url){
	if(speaker.point.mp3Object!=null){
		speaker.point.mp3Object.destruct();
	}
	speaker.point.mp3Object= soundManager.createSound({
                id:'sound',
                url:url,
                onfinish:pointcallback
        });
      speaker.point.mp3Object.play();
}
function pointcallback(){
	if(speaker.point.mp3Object!=null){
		speaker.point.mp3Object.destruct();
	}
}
//进行页面通过cookie初始化方法
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
//页面通过按钮操作方法
speaker.pointRead = function(){
	if(speaker.speakerStatus==false){
		speaker.speakerStatus = true;
		storage.setCookie("point_read",'open',360);
		$('#point_read').addClass('on');
		basic.dynamicIcon.change("point_read");
	}else{
		speaker.speakerStatus = false
		storage.setCookie("point_read",'close',360);
		$('#point_read').removeClass('on');
		basic.dynamicIcon.change("point_read");
	}
}
//开启即指即读后,调用此方法会发送请求朗读
speaker.point.speak = function (text) {
	if (speaker.speakerStatus == false) {
		return;
	}
	speaker.send(text);
};
speaker.send = function(text){
	if(text==null || text.length==0){
		return null;
	}
	var de= base64.e64(text);
   	$.ajax({
		type:'GET',
		url:speaker.url+'/ws/t2s',
		dataType:'jsonp',
		jsonp:"callback",
		data:{"b":de},
		async: true,
		success:function(data){
		    speaker.point.esdStart(data.u);
		}
   	})
}
//工具栏朗读==============================================================================================
speaker.toolbar = {};
speaker.toolbar.src="/assets/mp3/";
speaker.toolbar.speak = function (toolbar_id) {
	var url = speaker.toolbar.src + toolbar_id + ".mp3";
	if (speaker.toolbar) {
		speaker.toolbar.esdStart(url);
	}
};
speaker.toolbar.flg={};
speaker.toolbar.esdStart=function(url){
	if(speaker.toolbar.mp3Object!=null){
		speaker.toolbar.mp3Object.destruct();
	}
	speaker.toolbar.mp3Object=soundManager.createSound({
                id:'tool',
                url:url,
                onfinish:toolcallback
        });
     speaker.toolbar.mp3Object.play();
}
function toolcallback(){
	if(speaker.toolbar.mp3Object!=null){
		speaker.toolbar.mp3Object.destruct();
	}
}
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


	var tool_url = speaker.toolbar.src +"click/"+ toolbar_id + "_click.mp3";
	if (speaker.toolbar) {
		speaker.toolbar.esdStart(tool_url);
	}
};
