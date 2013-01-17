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
speaker.url = "http://125.211.222.45:8083";
speaker.index = 0;//连读索引
speaker.source = new Array();//连续缓存
speaker.continueStatus = false;
speaker.audioPlaying = false;
speaker.read_enabled = true;
speaker.mp3Object=null;//朗读语音对象

speaker.ws={};
speaker.ws.esdStart = function(url){
	speaker.mp3Object= soundManager.createSound({
                id:'sound',
                url:url,
                onfinish:callback
        });
      speaker.mp3Object.play();
}
//连读需要调用的方法
function playComplete() {
	if(speaker.toolbar.flg.speak==true){
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
// 播放完成回调方法
function callback() {
	speaker.mp3Object.destruct();
	playComplete();
}
 //停止朗读
speaker.stop = function () {
	$(speaker.source[speaker.index]).removeClass("tts_reading");
	speaker.index = 0;
	if (speaker.ws) {
		speaker.mp3Object.destruct();
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
	if(speaker.batchStatus==false){//关闭状态转为开启
		speaker.batchStatus=true;
		storage.setCookie("batch_read",'open',360);
		$('#batch_read').addClass('on');
		
		if(speaker!=null && speaker.mp3Object!=null){
			speaker.mp3Object.destruct();
		}
		speaker.index=0;
		setTimeout(function(){
			speaker.batch.speak(speaker.index);
		},3000);
	}else{
		speaker.batchStatus=false;
		storage.setCookie("batch_read",'close',360);
		$('#batch_read').removeClass('on');
		
		$(speaker.source[speaker.index]).removeClass("tts_reading");
		speaker.index = 0;
		if(speaker!=null && speaker.mp3Object!=null){
			speaker.mp3Object.destruct();
		}
	}
   
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
	var url = "/assets/mp3/" + toolbar_id + ".mp3";
	if (speaker.ws) {
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


	var tool_url = "/assets/mp3/click/" + toolbar_id + "_click.mp3";
	if (speaker.ws) {
		speaker.ws.esdStart(tool_url);
	}
};
// 朗读方法，唯一的对外接口
speaker.speak = function (text) {
	if(speaker!=null && speaker.mp3Object!=null){
		speaker.mp3Object.destruct();
	}
	var de= base64.e64(text);
    	$.ajax({
		type:'GET',
		url:speaker.url+'/ws/t2s',
		dataType:'jsonp',
		jsonp:"callback",
		data:{"b":de},
		async: false,
		success:function(data){
		    speaker.ws.esdStart(data.u);
		}
    	})
};

