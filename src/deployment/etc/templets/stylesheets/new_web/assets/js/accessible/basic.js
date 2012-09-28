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
basic.screenWidth.widthUnit=100; 
// 设置页面宽窄的方法
basic.screenWidth.setContentWidth = function(width) {
    $('#main').css('width', width + "px");
}
// 复位页宽
basic.screenWidth.resetScreenWidth = function(){
	basic.screenWidth.setContentWidth(basic.screenWidth.resetWidth);
}
// 增加页宽
basic.screenWidth.increaseScreenWidth = function() {
    var pxSize = parseInt($('#main').css('width').replace('px', ''));
    if(pxSize>basic.screenWidth.resetWidth+basic.screenWidth.widthUnit*5){
    	return;
    }
	pxSize = pxSize + basic.screenWidth.widthUnit;
    basic.screenWidth.setContentWidth(pxSize);
}
// 减少页宽
basic.screenWidth.decreaseScreenWidth = function() {
	var pxSize = parseInt($('#main').css('width').replace('px', ''));
	if(pxSize<basic.screenWidth.resetWidth-basic.screenWidth.widthUnit*4){
		return;
	}
	pxSize = pxSize - basic.screenWidth.widthUnit;
    basic.screenWidth.setContentWidth(pxSize);
}
basic.screenWidth.loadWidth = function(){
	basic.screenWidth.resetWidth = parseInt($('#main').css('width').replace('px', ''));
}

/**
 * 
 * 设置字体大小
 *
 */
basic.fontSize = {};
basic.fontSize.fontUnit=2; 
// 设置字体大小
basic.fontSize.setFontSize = function(size) {
	$('#main').css('font-size', size + 'px');
}
// 增加字号
basic.fontSize.increaseFont = function() {
	var pxSize = parseInt($('#main').css('font-size').replace('px', ''));
	if(pxSize>basic.fontSize.resetfont+basic.fontSize.fontUnit*6){
		return;
	}
	pxSize = pxSize + basic.fontSize.fontUnit;
    basic.fontSize.setFontSize(pxSize);
}
// 复位字体
basic.screenWidth.resetFont = function(){
	basic.fontSize.setFontSize(basic.fontSize.resetfont);
}
// 减少字号
basic.fontSize.decreaseFont = function() {
	var pxSize = parseInt($('#main').css('font-size').replace('px', ''));
	if(pxSize<basic.fontSize.resetfont-basic.fontSize.fontUnit*2){
		return;
	}
	pxSize = pxSize - basic.fontSize.fontUnit;
    basic.fontSize.setFontSize(pxSize);
}
basic.fontSize.loadSize = function(){
	basic.fontSize.resetfont = parseInt($('#main').css('font-size').replace('px', ''));
}
/**
 * 
 * 设置行距大小
 *
 */
basic.lineHeight = {};
basic.lineHeight.heightUnit=4; 
// 设置行距
basic.lineHeight.setLineHeight = function(size) {
	$('#main').css('line-height', size + 'px');
}
// 增加行距
basic.lineHeight.increaseHeight = function() {
	var pxHeight = parseInt($('#main').css('line-height').replace('px', ''));
	if(pxHeight>basic.lineHeight.resetHeight+basic.lineHeight.heightUnit*6){
		return;
	}
	pxHeight = pxHeight + basic.lineHeight.heightUnit;
    basic.lineHeight.setLineHeight(pxHeight);
}

basic.lineHeight.resetLineHeight= function() {
	basic.lineHeight.setLineHeight(basic.lineHeight.resetHeight);
}
// 减少行距
basic.lineHeight.decreaseHeight = function() {
	var pxHeight = parseInt($('#main').css('line-height').replace('px', ''));
	if(pxHeight<basic.lineHeight.resetHeight-basic.lineHeight.heightUnit*5){
		return;
	}
	pxHeight = pxHeight - basic.lineHeight.heightUnit;
    basic.lineHeight.setLineHeight(pxHeight);
}
// 载入之前的值
basic.lineHeight.loadHeight = function() {
	//$('body').css('line-height','24px');
    basic.lineHeight.resetHeight = parseInt($('#main').css('line-height').replace('px', ''));
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
	//var shouldLoad = storage.getCookie('show_guides');
	//if(shouldLoad) {
		basic.guides.showGuides();
	//} else {
		//basic.guides.hideGuides();
	//}
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
	$('.magnifier').css('display', 'block');
	$('body').css('padding-bottom', '200px');

}
// 隐藏放大镜
basic.magnifier.hideMagnifier = function() {
	$('.magnifier').css('display', 'none');
	$('body').css('padding-bottom', '0px');
}
// 开关放大镜
basic.magnifier.toggleMagnifier = function() {
    if ($('.magnifier').css('display') == 'block') {
    	basic.magnifier.hideMagnifier();    
    }
    else {
        basic.magnifier.showMagnifier();
    }
}
// 使用放大镜放大文字
basic.magnifier.magnifyIt = function(argument) {
	$('.screen div span').html(argument);
}
// 载入之前的设置
basic.magnifier.loadMagnifierStatus = function() {
	//var status = storage.getCookie('magnifier_status');
	//if(status == 1) {
		basic.magnifier.showMagnifier();
	//} else {
		//basic.magnifier.hideMagnifier();
	//}
}

/**
 * 
 * 显示主题替换
 *
 */
basic.changeTheme = {};
// 设置最终的CSS
basic.changeTheme.setActiveStyle = function(title) {
	$('head link[title="standard"]').attr('href','assets/css/'+title+'.css');
	// theme默认是关闭的
	/*
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
			//alert(a.getAttribute("title") + a.disabled.toString());
		}
	}

	if(title == 'standard') {
		$('#theme_standard').addClass('on');
		//$('.magnifier').css('background', '#EEE');
	} else if(title == 'dark') {
		$('#theme_dark').addClass('on');
		//$('.magnifier').css('background', '#333');
	} else {
		$('#theme_highcontrast').addClass('on');
		//$('.magnifier').css('background', 'navy');
	}
	*/

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
	basic.changeTheme.setActiveStyle('highcontrast');
}
// 载入之前的值
basic.changeTheme.loadStyle = function() {
/*
	var savedStyle = storage.getCookie('active_style');
    if(savedStyle) {
        basic.changeTheme.setActiveStyle(savedStyle);
    }
*/
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
	$('.mod_translate').css('display', 'block');
	//display:none
}

basic.translator.hideResult = function() {
	$('.mod_translate').css('display', 'none');
}
basic.translator.toggleTranslate = function() {
/*
		if ($('#toggle_translate').hasClass('item_71')) {
			$('#toggle_translate').removeClass('item_71').addClass('item_21');
		};
*/
	$('#toggle_translate').toggle();
	
	if ($(".tts_data").HasBubblePopup()) {
		$(".tts_data").RemoveBubblePopup();
	} else {
	    // VOIDMAIN
    $(".tts_data").each(function(index, element) {
      $(this).CreateBubblePopup({
        innerHtml: '<img src="assets/img/translating.gif"/><p>正在翻译...</p>',
        position: 'top',
        align: 'left',
        openingDelay: 0,
        // hack: 这些并不是泡泡类库的标准方法，但是因为它实际就是一个JS对象，
        //       所以可以动态添加一些属性
        //       oriElement表示的是鼠标移动到哪个元素对应的那一个泡泡
        //       text2trans表示的是对应的哪个泡泡的文字内容
        oriElement: $(element),
        text2trans: $(element).text(),
        afterShown: function() {
          // VOIDMAIN hack：这里引入一个saved方法记录是否已经翻译过（或正在翻译）这个内容
          if (!this.saved) {
            this.saved = true;
            var text = this.text2trans;
            trans.doTranslate(text, basic.translator.showTransResult, this.oriElement);
          };
        }
      });
    });
	}
}
// VOIDMAIN
// 回调的回调，用于显示结果
basic.translator.showTransResult = function(statusCode, result, element) {
  if (!statusCode) {
    result = "<p class='trans_succ'>" + result + "</p>";
  } else {
    result = "<p class='trans_fail'>" + result + "</p>";
  }
  element.SetBubblePopupInnerHtml(result);
}
/**
 * 
 * 还原页面
 *
 */
basic.resetpage = {}
basic.resetpage.reset = function(){
	basic.screenWidth.resetScreenWidth();
	basic.screenWidth.resetFont();
	basic.lineHeight.resetLineHeight();
	basic.magnifier.hideMagnifier();
	basic.guides.hideGuides();
	speaker.stop();
	basic.changeTheme.changeToStandard();
}
 
 
 
 
/**
 * 
 * 横竖版式切换
 *
 */
 /*
basic.styleSwitcher = {};
// 切换为竖版
basic.styleSwitcher.changeToVert = function() {
	$('#xory').removeClass('top-y');
	$('#xory').removeClass('top-x');
	$('#xory').addClass('top-y');

	//storage.setCookie('hori_vert_status', 'y');
}
// 切换为横版
basic.styleSwitcher.changeToHori = function() {
	$('#xory').removeClass('top-x');
	$('#xory').removeClass('top-y');
	$('#xory').addClass('top-x');

	//storage.setCookie('hori_vert_status', 'x');
}
// 开关放大镜
basic.styleSwitcher.toggleStyle = function() {
    if ($('#xory').hasClass('top-x')) {
    	basic.styleSwitcher.changeToVert();
    }
    else {
        basic.styleSwitcher.changeToHori();
    }
}
*/
// 载入之前的设置
//basic.styleSwitcher.loadStyleStatus = function() {
	//var status = storage.getCookie('hori_vert_status');
	//if(status == 'y') {
		//basic.styleSwitcher.changeToVert();
	//} else {
		//basic.styleSwitcher.changeToHori();
	//}
//}
