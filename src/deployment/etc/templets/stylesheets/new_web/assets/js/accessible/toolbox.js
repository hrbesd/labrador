/**
 * 工具箱的调度模块
 *
 * 主要完成的功能是工具栏界面显示与对应JS功能实现的绑定
 * 而具体模块功能的实现，则是放到单独的实现文件之中
 * 工具箱主要的功能就是将界面上html标签中的id与对应的实现代码绑定起来
 *
 * Author： Void Main
 */
var initContent = function() {
	var t2sUrl="http://125.211.222.45:8083/ws/batch";
  	var arr = new Array();
	$("span[class=tts_data]").each(function(){
	  	var de= base64.e64($(this).text());
	  	arr.push(de);
	  	//保正不能超过5句,每句不能超过100字
	  	if(arr.length>5){
	 		$.ajax({
			    type:'GET',
			    url:t2sUrl,
			    dataType:'jsonp',
			    jsonp:"callback",
			    data:{"b":arr},
			    async: true
	    	});
	    	//清空缓存
	 	 	arr=new Array();
		}
  	});
  	//把缓存没有满5句的发送
  	if(arr.length>0){
 	 	$.ajax({
		    type:'GET',
		    url:t2sUrl,
		    dataType:'jsonp',
		    jsonp:"callback",
		    data:{"b":arr},
		    async: true
	    });
  	}
  	arr = new Array();//清空缓存


}
//加载swf成功后调用的方法
function initSM2(){
    // 在ready的时候，载入各种工具箱工具的状态
    loadStatus();
    // 绑定界面元素事件
    bindActions();
	// 绑定键盘快捷键
    $(document).keydown(function(event){
        keybinding.processKeyEvent(event);
    });
}

jQuery(document).ready(function(){
	initContent();
	//初始化soundManager播放器
	soundManager.setup({
	  useFlashBlock: false,
	  flashVersion:9,
	  url: '/assets/swf/', 
	  debugMode: false,
	  consoleOnly: false,
	  onready:initSM2
	});
	//补足5个子目录
	$('li[class=bulletin] ul').each(function(){
	      var len = $(this).children('li').size();
	      var w = 5-len;
	      for(var i=0;i<w;i++){
	      	//$(this).append("<ul style='list-style:none; '><li>&nbsp;</li></ul>");
	      	$(this).append("<ul style='list-style:none; list-style-image: url(\"/assets/img/list-style-image-empty.png\");'><li>&nbsp;</li></ul>");
	      }
	 });
	 /*
    	// 在ready的时候，载入各种工具箱工具的状态
    	loadStatus();

    	// 绑定界面元素事件
    	bindActions();

	// 绑定键盘快捷键
	$(document).keydown(function(event){
        keybinding.processKeyEvent(event);
    	});
      	*/
});

// 载入之前保存的修改
// 这里载入所有可能的已保存的值
var loadStatus = function() {
    //speaker.loadSpeakerStatus();
    basic.screenWidth.loadWidth();
    basic.fontSize.loadSize();
    basic.lineHeight.loadHeight();
    basic.changeTheme.loadStyle();
    basic.guides.loadGuides();
    basic.magnifier.loadMagnifierStatus();
    speaker.loadPointRead();
    speaker.loadBatchRead();
    basic.translator.loadTranslator();
    basic.dynamicIcon.change("null");//初始化动态更换的图标
    //basic.styleSwitcher.loadStyleStatus();
};

var intervalId;
var toolIntervalId;
// 绑定各个id对应执行的操作
var bindActions = function() {
    $('#should_read').click(action.toggleSpeak);
    $('#increase_width').click(action.increaseScreenWidth);
    $('#reset_width').click(action.resetScreenWidth);
    $('#decrease_width').click(action.decreaseScreenWidth);
    $('#text_in').click(action.increaseFontSize);
    $('#reset_text').click(action.resetFontSize);
    $('#text_out').click(action.decreaseFontSize);
    $('#line_height_in').click(action.increaseLineHeight);
    $('#line_height_reset').click(action.resetLineHeight);
    $('#line_height_out').click(action.decreaseLineHeight);
    $('#guides').click(action.toggleGuides);
    $('#toggle_magnifier').click(action.toggleMagnifier);
    $('#toggle_speaker').click(action.toggleSpeak);
   // $('#switch_hori_vert').click(action.toggleStyle);
    $('#reset_page').click(action.restPage);
    $('#toggle_translate').click(action.toggleTranslate);

    $('#point_read').click(action.point_read);
    $('#close_read').click(action.close_read);
    $('#batch_read').click(action.batch_read);

    $('span[class=tts_data]').each(function() {
        $(this).bind("mouseover", function() {
    		//放大镜添加事件
            basic.magnifier.magnifyIt(this.innerHTML);
            $('.magnifier').textfill({ maxFontPixels: 160 });
        });
	//鼠标进入事件
        $(this).bind("mouseenter", function() {
	        //window.clearTimeout(intervalId);
	        //设置焦点。焦点中会发送请求朗读功能
	        $(this).parents('a').focus();
	        var obj=$(this);
    		intervalId=setTimeout(function(){
		    if(speaker.speakerStatus==true){
		    	speaker.point.speak(obj.text());
		    	obj.addClass("tts_reading");
		    }
		 },2000);
        });
        //鼠标移出事件
        $(this).bind("mouseleave", function() {
        	window.clearTimeout(intervalId);
	        if(speaker.speakerStatus==true){
	        	$(this).removeClass("tts_reading");
	        }
        });
        //鼠标右键屏蔽菜单
        //$(this).bind("contextmenu", function() {
        //	return false;
        //});
    });
	//朗读功具栏语音
    $('div[id=toolbar] a').each(function() {
        $(this).bind("mouseenter", function() {
		speaker.toolbar.speak($(this).attr("id"));
        });
        $(this).bind("mouseleave", function() {

        });
        $(this).bind("click", function() {
        	var toolbar_id = $(this).attr("id")
        	speaker.toolbar.click(toolbar_id);
        	basic.dynamicIcon.change(toolbar_id);
        });
        $(this).bind("focus", function() {
		speaker.toolbar.speak($(this).attr("id"));
        });
    });
    //切换焦点
    /*
    $('span[class=tts_data]').parents('a').each(function() {
    	$(this).bind("focus", function() {
    		//如果批量朗读开起不会读取，因为连读会焦点跟随产生重读。
    		if(speaker.batchStatus==false){
    			var children = $(this).contents('.tts_data')
    			intervalId=setTimeout(function(){
		            if(speaker.speakerStatus==true){
		            	speaker.point.speak(children.html());
		    			children.addClass("tts_reading");
		            }
		         },2000);
    		}
        });
    	$(this).bind("blur", function() {
    		$(this).contents('.tts_data').removeClass("tts_reading");
        });
    });
        */

    // change themes
    // change stylesheet button
    $('#theme_standard').click(action.changeToStandardTheme);
    $('#theme_dark').click(action.changeToDarkTheme);
    $('#theme_highcontrast').click(action.changeToHightContrastTheme);

};

var transCallback = function(result, element) {
    var pos = findPosition(element);
    basic.translator.showResult(pos[0], pos[1], result);
}

function findPosition( oElement )
{
    var top = oElement.offset().top;
    var left = oElement.offset().left;
    return [top, left];
}

function accessible(){
    if (!$('#acctoolbar')[0]) {
        accessible_enable = true;

        //ie6 style hack
        if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
            $('#acctoolbar').css('position', 'absolute');
            $(window).scroll(function(){
                $('#acctoolbar').css('top', $(window).scrollTop());
            })
        }

        //close button
        $('#accclose').click(function(){
            accessible_enable = false;

            if (parseInt($('body').css('font-size').replace('px', ''), 10) != 12) {
                $('body').css('font-size', '12px');
            }

            // change back to standard style
            setActiveStyleSheet('standard');

            if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
                $(window).unbind("scroll");
            }

            if ($('#guides_horiz')[0]) {
                $('#guides_horiz,#guides_verti').remove();
                $('body').unbind("mousemove");
                if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
                    $(window).unbind("resize");
                }
            }

            $('#acctoolbar').remove();
            $('#wrapper').css('padding-top', 0);

            //remove cookie
            storage.eraseCookie('accessible');
        });

        //save cookie
        storage.setCookie('accessible', 1, 360);
    }
    return false;
}

