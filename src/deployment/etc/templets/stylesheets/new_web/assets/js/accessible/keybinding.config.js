/**
 * 键盘绑定配置文件
 *
 * 键盘绑定是一系列可以更改的键值对，其中键是键盘的按键编码，值是对应函数的名称。
 * 这里的按键已经默认按下了ctrl+shift两个键，不再对这两个键有别的需求。
 * 如果后续需要扩展，再进行添加
 * 
 * “包”名： keybinding.config
 *
 * Author: Void Main
 2.	对以下功能进行快捷键定义。
	1)	正常模式 Ctrl+Shift+ + n （normal）
	2)	黑夜模式 Ctrl+Shift+ + b  （black）
	3)	高对比度模式 Ctrl+Shift+ + h （high）
	4)	放大字体   Ctrl+Shift+ + u
	5)	还原字体   Ctrl+Shift+ + i
	6)	缩小字体   Ctrl+Shift+ + o
	7)	增加页宽   Ctrl+Shift+ + j
	8)	减小页宽   Ctrl+Shift+ + k
	9)	还原页宽   Ctrl+Shift+ + l
	10)	增加行距   Ctrl+Shift+ + m
	11)	减小行距   Ctrl+Shift+ + ,
	12)	还原行距   Ctrl+Shift+ + .
	13)	关闭/开启自动朗读功能 Ctrl+Shift+ + r(read)
	14)	关闭/开启即指即读功能 Ctrl+Shift+ + c (click)
	15)	翻译功能  Ctrl+Shift+ + / （translator）
	16)	放大镜功能  Ctrl+Shift+ + d （magnifier）
	17)	辅助线功能  Ctrl+Shift+ + g (guide)
	18)	无障碍说明  Ctrl+Shift+ + a (instruction)
	19)	焦点朗读功能  Ctrl+Shift+ + f  (focus)
	20)	正文朗读功能   Ctrl+Shift+ + p (paragraph)
 */
var keybinding={};
keybinding.bind=function(){
	//模式======================================================================
	//正常模式
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+n',function (evt){
		action.changeToStandardTheme();
        	speaker.toolbar.click("theme_standard");
        	return false;
	});
	//黑夜模式
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+b',function (evt){
		action.changeToDarkTheme();
        speaker.toolbar.click("theme_dark");
        	return false;
	});
	//高亮模式
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+h',function (evt){
		action.changeToHightContrastTheme();
        	speaker.toolbar.click("theme_highcontrast");
       		return false;
	});
	//字体======================================================================
	//字体放大
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+u',function (evt){
		action.increaseFontSize();
        	speaker.toolbar.click("text_in");
        	return false;
	});
	//字体还原
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+i',function (evt){
		action.resetFontSize();
        	speaker.toolbar.click("reset_text");
        	return false;
	});
	//字体缩小
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+o',function (evt){
		action.decreaseFontSize();
        speaker.toolbar.click("text_out");
        return false;
	});
	//页宽======================================================================
	//页宽放大
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+j',function (evt){
		action.increaseScreenWidth();
        	speaker.toolbar.click("increase_width");
        return false;
	});
	//还原页宽
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+k',function (evt){
		action.resetScreenWidth();
        	speaker.toolbar.click("reset_width");
        return false;
	});
	//页宽缩小
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+l',function (evt){
		action.decreaseScreenWidth();
        	speaker.toolbar.click("decrease_width");
       return false;
	});
	//行距======================================================================
	//行距放大
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+m',function (evt){
		action.increaseLineHeight();
        	speaker.toolbar.click("line_height_in");

        return false;
	});
	//还原行距
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+,',function (evt){
		action.resetLineHeight();
        	speaker.toolbar.click("line_height_reset");
        return false;
	});
	//行距缩小
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+.',function (evt){
		action.decreaseLineHeight();
       		speaker.toolbar.click("line_height_out");
       return false;
	});
	//语音======================================================================
	//自动朗读
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+r',function (evt){
		action.batch_read();
        	speaker.toolbar.click("batch_read");
        	return false;
	});
	//即指即读
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+c',function (evt){
		action.point_read();
        	speaker.toolbar.click("point_read");
        	return false;
	});
	//翻译
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+/',function (evt){
		action.toggleTranslate();
        	speaker.toolbar.click("toggle_translate");
        //basic.dynamicIcon.change(toolbar_id);
       return false;
	});
	//放大镜
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+e',function (evt){
		action.toggleMagnifier();
       		speaker.toolbar.click("toggle_magnifier");
       		return false;
       
	});
	//辅助线
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+g',function (evt){
		action.toggleGuides();
      		speaker.toolbar.click("guides");
       		return false;
       
	});
	//无障碍说明
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+a',function (evt){
		speaker.toolbar.click("accessibility");
	   	setTimeout("window.open('accessible.xml')", 1000);
       		return false;
       
	});
	//焦点朗读
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+p',function (evt){
		if(speaker.bodyTextStatus==true){
			speaker.bodyTextStatus=false;
			speaker.toolbar.click("body_un");
		}else{
			//如果自动朗读以开启
			if(speaker.batchStatus==true){
				//action.batch_read();
				speaker.batchRead();
			}
			speaker.bodyTextStatus=true;
			speaker.toolbar.click("body");
		}
		speaker.batchRead();
      		 return false;
       
	});
	//帮助
	jQuery_1_3_2(document).bind('keydown', 'alt+f1',function (evt){
       	return false;
	});
	//朗读功能快捷键使用说明-2015-02-06修改 start
	speaker.toolbar.hotkeyMp3ObjectFlg=false;
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+s',function (evt){
		if(speaker.toolbar.hotkeyMp3ObjectFlg==true){
			return;
		}
		speaker.toolbar.hotkeyMp3ObjectFlg=true;
		speaker.toolbar.hotkeyMp3Object=soundManager.createSound({
            id:'hotkey',
            url:speaker.toolbar.src+"toolbarHotkey.mp3",
            onfinish:function(){
            	speaker.toolbar.hotkeyMp3Object.destruct();
				speaker.toolbar.hotkeyMp3ObjectFlg=false;
            }
		});
	
		speaker.toolbar.hotkeyMp3Object.play();
       	return false;
       
	});
	//关闭朗读功能快捷键使用说明
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+f',function (evt){
		if(speaker.toolbar.hotkeyMp3Object != null){
			speaker.toolbar.hotkeyMp3Object.destruct();
			speaker.toolbar.hotkeyMp3ObjectFlg=false;
		}
       	return false;
	});
	//关闭和开启焦点朗读供能
	speaker.toolbar.tabIndex=false;
	jQuery_1_3_2(document).bind('keydown', 'alt+shift+1',function (evt){
		if(speaker.toolbar.tabIndex==false){
			speaker.toolbar.tabIndex=true;
			$('#main a,#footer_links a,#main input').each(function() {
				if(this.tagName=='INPUT'){
					var type = $(this).attr("type");
					if(type=='hidden'){
						$(this).blur();
						return;
					}
				}
				
				$(this).bind("focus", function() {
					if(speaker.batchStatus==false && speaker.speakerStatus==false){
						if(this.tagName=='INPUT'){
							var value = $(this).attr("alt");
							focusvalId=setTimeout(function(){
								speaker.send(value);
							}, 300);
						}else if(this.tagName=='A'){
							var children = $(this).find("span[class=tts_data]");
							focusvalId=setTimeout(function(){
								speaker.send(children.text());
							}, 300);
						}
			
					}
				});
				$(this).bind("blur", function() {
					window.clearTimeout(focusvalId);
			
				});
				
			});
		}else{
			speaker.toolbar.tabIndex=false;
			$('#main a,#footer_links a,#main input').each(function() {
				if(this.tagName=='INPUT'){
					var type = $(this).attr("type");
					if(type=='hidden'){
						$(this).unbind("blur");;
						return;
					}
				}
				
				$(this).unbind("focus");
				$(this).unbind("blur");
				
			});
		}
	});
};
