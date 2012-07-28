/**
 * 提供辅助工具箱的基本功能
 *
 * 包括字体、页面宽窄、字号等等在内的基本功能
 * “包”名： basic
 *
 * Author: Void Main
 */

var basic = {};

/**
 *
 * 设置页面宽窄
 *
 */
basic.screenWidth = {};
// 设置页面宽窄的方法
basic.screenWidth.setContentWidth = function(width) {
	storage.setCookie('content_width', width, 360);
    $('#main').css('width', width + "px");
}
// 增加页宽
basic.screenWidth.increaseScreenWidth = function() {
    var pxSize = parseInt($('#main').css('width').replace('px', ''));
	pxSize = pxSize + 100;
    basic.screenWidth.setContentWidth(pxSize);
}
// 减少页宽
basic.screenWidth.decreaseScreenWidth = function() {
	var pxSize = parseInt($('#main').css('width').replace('px', ''));
	pxSize = pxSize - 100;
    basic.screenWidth.setContentWidth(pxSize);
}
// 载入之前的值
basic.screenWidth.loadWidth = function() {
	var contentWidth = storage.getCookie('content_width');
    if(contentWidth) {
        basic.screenWidth.setContentWidth(contentWidth);
    }
}

/**
 * 
 * 设置字体大小
 *
 */
basic.fontSize = {};
// 设置字体大小
basic.fontSize.setFontSize = function(size) {
	storage.setCookie('font_size', size, 360);
	$('html').css('font-size', size + 'px');
}
// 增加字号
basic.fontSize.increaseFont = function() {
	var pxSize = parseInt($('html').css('font-size').replace('px', ''));
	pxSize = pxSize + 2;
    basic.fontSize.setFontSize(pxSize);
}
// 减少字号
basic.fontSize.decreaseFont = function() {
	var pxSize = parseInt($('html').css('font-size').replace('px', ''));
	pxSize = pxSize - 2;
    basic.fontSize.setFontSize(pxSize);
}
// 载入之前的值
basic.fontSize.loadSize = function() {
	var savedSize = storage.getCookie('font_size');
    if(savedSize) {
        basic.fontSize.setFontSize(savedSize);
    }
}

/**
 * 
 * 设置行距大小
 *
 */
basic.lineHeight = {};
// 设置行距
basic.lineHeight.setLineHeight = function(size) {
	storage.setCookie('line_height', size, 360);
	$('body').css('line-height', size + 'px');
}
// 增加行距
basic.lineHeight.increaseHeight = function() {
	var pxHeight = parseInt($('body').css('line-height').replace('px', ''));
	pxHeight = pxHeight + 4;
    basic.lineHeight.setLineHeight(pxHeight);
}
// 减少字号
basic.lineHeight.decreaseHeight = function() {
	var pxHeight = parseInt($('body').css('line-height').replace('px', ''));
	pxHeight = pxHeight - 4;
    basic.lineHeight.setLineHeight(pxHeight);
}
// 载入之前的值
basic.lineHeight.loadHeight = function() {
	var savedHeight = storage.getCookie('line_height');
    if(savedHeight) {
        basic.lineHeight.setLineHeight(savedHeight);
    }
}

/**
 * 
 * 辅助线开关
 *
 */
basic.guides = {};
// 开启辅助线
basic.guides.showGuides = function() {
	$('body').append('<div id="guides_horiz"></div><div id="guides_verti"></div>').mousemove(function(pos){
	    $('#guides_horiz').css('top', pos.clientY + 10 + $(document).scrollTop());
	    $('#guides_verti').css('left', pos.clientX + 10).css('top', $(document).scrollTop());
	});
	if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
	    $('#guides_verti').css('height', $(window).height());
	    $(window).resize(function(){
	        ('#guides_verti').css('height', $(window).height());
	    });
	}

	$('#guides').addClass('on');
}
// 关闭辅助线
basic.guides.hideGuides = function() {
	$('#guides_horiz,#guides_verti').remove();
    $('body').unbind("mousemove");
    if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
        $(window).unbind("resize");
    }

    $('#guides').removeClass('on');
}
// 载入之前的设置
basic.guides.loadGuides = function() {
	var shouldLoad = storage.getCookie('show_guides');
	if(shouldLoad) {
		basic.guides.showGuides();
	} else {
		basic.guides.hideGuides();
	}
}
// 开关辅助线
basic.guides.toggleGuides = function() {
    if ($('#guides_horiz')[0]) {
    	basic.guides.hideGuides();    
    }
    else {
        basic.guides.showGuides();
    }
}

/**
 * 
 * 放大镜开关
 *
 */
basic.magnifier = {};
// 显示放大镜
basic.magnifier.showMagnifier = function() {
	$('.magnifier').css('visibility', 'visible');
	$('body').css('padding-bottom', '200px');

	storage.setCookie('magnifier_status', 1, 360);
}
// 隐藏放大镜
basic.magnifier.hideMagnifier = function() {
	$('.magnifier').css('visibility', 'hidden');
	$('body').css('padding-bottom', '20px');

	storage.eraseCookie('magnifier_status');
}
// 开关放大镜
basic.magnifier.toggleMagnifier = function() {
    if ($('.magnifier').css('visibility') == 'visible') {
    	basic.magnifier.hideMagnifier();    
    }
    else {
        basic.magnifier.showMagnifier();
    }
}
// 使用放大镜放大文字
basic.magnifier.magnifyIt = function(argument) {
	$('#magnified').html(argument);
}
// 载入之前的设置
basic.magnifier.loadMagnifierStatus = function() {
	var status = storage.getCookie('magnifier_status');
	if(status == 1) {
		basic.magnifier.showMagnifier();
	} else {
		basic.magnifier.hideMagnifier();
	}
}

/**
 * 
 * 显示主题替换
 *
 */
basic.changeTheme = {};
// 设置最终的CSS
basic.changeTheme.setActiveStyle = function(title) {
	storage.setCookie('active_style', title, 360);
	
	// theme默认是关闭的
	$('#theme_standard').removeClass('on');
	$('#theme_dark').removeClass('on');
	$('#theme_highcontrast').removeClass('on');

	var i, a;
	for(i=0; (a = document.getElementsByTagName("link")[i]); i++) {
		if(a.getAttribute("rel").indexOf("style") != -1
			&& a.getAttribute("title")) {
			// if the title of the selected style does not match
			// then, disable it
			a.disabled = (a.getAttribute("title") != title);
		}
	}

	if(title == 'standard') {
		$('#theme_standard').addClass('on');
		$('.magnifier').css('background', '#EEE');
	} else if(title == 'dark') {
		$('#theme_dark').addClass('on');
		$('.magnifier').css('background', '#333');
	} else {
		$('#theme_highcontrast').addClass('on');
		$('.magnifier').css('background', 'navy');
	}
	
}
// 设为正常主题
basic.changeTheme.changeToStandard = function() {
	basic.changeTheme.setActiveStyle('standard');
}
// 设为黑夜模式
basic.changeTheme.changeToDark = function() {
	basic.changeTheme.setActiveStyle('dark');
}
// 设为高对比度模式
basic.changeTheme.chageToHightContrast = function() {
	basic.changeTheme.setActiveStyle('high_contrast');
}
// 载入之前的值
basic.changeTheme.loadStyle = function() {
	var savedStyle = storage.getCookie('active_style');
    if(!savedStyle) {
        savedStyle = "standard";
    }
    basic.changeTheme.setActiveStyle(savedStyle);
}

/**
 *
 * 显示翻译结果
 *
 *
 */
basic.translator = {}
basic.translator.showResult = function(top, left, text) {
	$('.mod_translate').css('top', (top - 100) + 'px');
	$('.mod_translate').css('left', left + 'px');
	$('.mod_translate p').text(text);
	$('.mod_translate').css('visibility', 'visible');
}

basic.translator.hideResult = function() {
	$('.mod_translate').css('visibility', 'hidden');
}

/**
 *
 * 帮助界面
 *
 */
basic.help = {};
// 显示放大镜
basic.help.showHelp = function() {
	$('#help_layer').css('visibility', 'visible');
	$('#help_layer_bg').css('visibility', 'visible');
}
// 关闭放大镜
basic.help.hideHelp = function() {
	$('#help_layer').css('visibility', 'hidden');
	$('#help_layer_bg').css('visibility', 'hidden');
}