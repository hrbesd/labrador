/**
 * 语言翻译模块
 *
 * 调用Web Service获取某段中文内容的对应翻译
 * 这里假定原始文字信息是中文的
 * “包”名： trans
 *
 * Author: Void Main
 */

var trans = {};
// VOIDMAIN 修改了对应的TransCache的IP
//trans.baseURL = "http://125.211.222.44:9999/translate/en/";

// 翻译对应的内容
// 参数：text - 要翻译的文字
//      callback - 翻译的结果，返回的是字符串内容
trans.doTranslate = function(text, callback, element) {
	var src = text;
	var b64 = base64.e64(src);
	url = "http://voice.yunmd.net/baidu-translate-r1.0/translate";
	$.ajax({
		url : url,
		type : 'POST',
		data : {src:b64},
		success : function(e) {
			// alert(e.trans_result[0].dst);
			callback(0, e.trans_result[0].dst, element);
		},
		error : function(jqXHR, textStatus) {
			callback(1, textStatus, element);
		},
		dataType : 'jsonp',
		async : false
	});
	
	// 发送AJAX请求
	//var translateURL = trans.baseURL + text;
/*
    var translateURL = trans.baseURL + encodeURIComponent(text);
    $.ajax({
    url:translateURL,
    dataType: 'jsonp',
    jsonp: false,
    jsonpCallback: 'trans_result',
    type:'GET',
    success: function(dataJSON)
    {
      if(callback) {
      	callback(0, dataJSON.data.translations[0].translatedText, element);
      }
    },
    error: function(jqXHR, textStatus) {
    	callback(1, textStatus, element);
    }
	});
	*/
}
