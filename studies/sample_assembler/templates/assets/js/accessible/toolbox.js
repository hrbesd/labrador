/**
 * 工具箱的调度模块
 * 
 * 主要完成的功能是工具栏界面显示与对应JS功能实现的绑定
 * 而具体模块功能的实现，则是放到单独的实现文件之中
 * 工具箱主要的功能就是将界面上html标签中的id与对应的实现代码绑定起来
 * 
 * Author： Void Main
 */

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
};


// 绑定各个id对应执行的操作
var bindActions = function() {
    $('#should_read').click(action.toggleSpeak);
    $('#width_high').click(action.screenWidthHigh);
    $('#width_normal').click(action.screenWidthNormal);
    $('#width_low').click(action.screenWidthLow);
    $('#text_in').click(action.increaseFontSize);
    $('#text_out').click(action.decreaseFontSize);
    $('#line_height_in').click(action.increaseLineHeight);
    $('#line_height_out').click(action.decreaseLineHeight);

    $('#show_help').click(function() {
        ui.seperateLayer(100, 200, 800, 600, "<h1>测试弹出层</h1>");
    });

    $('#guides').click(action.toggleGuides);
};

// change active style sheet
function setActiveStyleSheet(title) {
   var i, a;
   for(i=0; (a = document.getElementsByTagName("link")[i]); i++) {
     if(a.getAttribute("rel").indexOf("style") != -1
        && a.getAttribute("title")) {
        // if the title of the selected style does not match
        // then, disable it
        a.disabled = (a.getAttribute("title") != title);
     }
   }
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

        // change stylesheet button
        $('#theme_standard').click(function() {
            setActiveStyleSheet('standard');
        });

        $('#theme_dark').click(function() {
            setActiveStyleSheet('dark');
        });

        $('#theme_highcontrast').click(function() {
            setActiveStyleSheet('high_contrast');
        });

        
        
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

