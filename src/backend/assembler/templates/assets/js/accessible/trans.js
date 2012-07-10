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
trans.baseURL = "http://localhost:9999/translate/en/";

// 翻译对应的内容
// 参数：text - 要翻译的文字
//      callback - 翻译的结果，返回的是字符串内容
trans.doTranslate = function(text, callback) {
	var translateURL = trans.baseURL + text;
	$.ajax({
	    url:translateURL,
	    type:'GET',
	    success: function(data)
	    {
	        dataJSON = JSON.parse(data);
	        if(callback) {
	        	callback(dataJSON.data.translations[0].translatedText);
	        }
	    }
	}); 
}
