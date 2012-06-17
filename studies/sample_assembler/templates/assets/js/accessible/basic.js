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
// 记录内容宽度，0-很宽，1-正常，2-很窄
basic.screenWidth.widthType = 1;
// 设置页面宽窄的方法
basic.screenWidth.setContentWidth = function(type) {
    var width = 100 - 20 * type;
    var left = type * 10;

    $('html').css('width', width + '%');
    $('html').css('padding-left', left + '%');

    storage.setCookie('content_width', type, 360);
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
}
// 关闭辅助线
basic.guides.hideGuides = function() {
	$('#guides_horiz,#guides_verti').remove();
    $('body').unbind("mousemove");
    if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
        $(window).unbind("resize");
    }
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