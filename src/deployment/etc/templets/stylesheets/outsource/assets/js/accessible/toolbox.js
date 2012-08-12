/**
 * 工具箱的调度模块
 * 
 * 主要完成的功能是工具栏界面显示与对应JS功能实现的绑定
 * 而具体模块功能的实现，则是放到单独的实现文件之中
 * 工具箱主要的功能就是将界面上html标签中的id与对应的实现代码绑定起来
 * 
 * Author： Void Main
 */
var initSM2 = function() {
    // flash version URL switch (for this demo page)
    var winLoc = window.location.toString();
    soundManager.setup({
      preferFlash: (winLoc.match(/usehtml5audio=1/i) ? false : true)
    });
    if (winLoc.match(/flash9/i)) {
        soundManager.setup({
            flashVersion: 9
        });
        if (winLoc.match(/highperformance/i)) {
            soundManager.setup({
              useHighPerformance: true
            });
        }
    } else if (winLoc.match(/flash8/i)) {
        soundManager.setup({
            flashVersion: 8
        });
    }

    soundManager.setup({
        useFlashBlock: false,
        url: 'assets/swf/',
        debugMode: true,
    });
}

initSM2();

jQuery(document).ready(function(){
    // 在ready的时候，载入各种工具箱工具的状态
    loadStatus();

    // 绑定界面元素事件
    bindActions();
	
	// 绑定键盘快捷键
	$(document).keydown(function(event){
        keybinding.processKeyEvent(event);
    });
});

// 载入之前保存的修改
// 这里载入所有可能的已保存的值
var loadStatus = function() {
    speaker.loadSpeakerStatus();
    basic.screenWidth.loadWidth();
    basic.fontSize.loadSize();
    basic.lineHeight.loadHeight();
    basic.changeTheme.loadStyle();
    basic.magnifier.loadMagnifierStatus();
    basic.styleSwitcher.loadStyleStatus();
};


// 绑定各个id对应执行的操作
var bindActions = function() {
    $('#should_read').click(action.toggleSpeak);
    $('#increase_width').click(action.increaseScreenWidth);
    $('#decrease_width').click(action.decreaseScreenWidth);
    $('#text_in').click(action.increaseFontSize);
    $('#text_out').click(action.decreaseFontSize);
    $('#line_height_in').click(action.increaseLineHeight);
    $('#line_height_out').click(action.decreaseLineHeight);
    $('#guides').click(action.toggleGuides);
    $('#toggle_magnifier').click(action.toggleMagnifier);
    $('#toggle_speaker').click(action.toggleSpeak);
    $('#switch_hori_vert').click(action.toggleStyle);

    $('data').each(function() {
        $(this).bind("mouseover", function() {
            basic.magnifier.magnifyIt(this.innerHTML);  
        });
    });

    /*$('data').each(function() {
        $(this).bind("mouseover", function() {
            trans.doTranslate(this.innerHTML, $(this), transCallback);  
        });
    }); */

    $('data').each(function() {
        $(this).bind("mouseover", function() {
            speaker.speak(this.innerHTML);
        });
    });

    /*
    $('data').each(function() {
        $(this).bind("mouseleave", function() {
            basic.translator.hideResult();
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

