/**
 * 工具栏的调度部分
 * 
 * 主要完成的功能是工具栏界面显示与对应JS功能实现的绑定
 * 而具体模块功能的实现，则是放到单独的实现文件之中
 * 
 * Author： Void Main
 */
// 记录内容宽度，0-很宽，1-正常，2-很窄
var widthType;

jQuery(document).ready(function(){

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

    function setContentWidth(type) {
        var width = 100 - 20 * type;
        var left = type * 10;

        $('body').css('width', width + '%');
        $('body').css('left', left + '%');
    }
  
	var accessible_enable = false;
  
    if (storage.getCookie('accessible') == 1) {
        accessible();
    }

    // toggle read
    if (storage.getCookie('read_the_words') == 1) {
        speaker.read_enabled = true;
    } else {
        speaker.read_enabled = false;
    }

    updateStatus();
	
	// ctrl + shirt + S  high contrast
	$(document).keydown(function(event){
        if (event.ctrlKey && event.shiftKey && event.keyCode == '83') {
            accessible();
        }
    });
    
	//attach click event accessible 
	$('#accessible').click(accessible);
	
    function accessible(){
        if (!$('#acctoolbar')[0]) {
			accessible_enable = true;
			
			//initial buttons
            var buttonHtml = '<div id="acctoolbar">' + 
                    '<button id="textin">文字放大</button>' +
                    '<button id="textout">文字缩小</button>' + 
                    '<button id="guides">辅助线</button>' + 
                    '<button id="theme_standard">基本主题</button>' + 
                    '<button id="theme_dark">黑色主题</button>' +
                    '<button id="theme_highcontrast">高对比度主题</button>' +
                    '<button id="width_high">很宽</button>' +
                    '<button id="width_normal">正常</button>' +
                    '<button id="width_low">很窄</button>' +
                    '<button id="should_read">关闭声音朗读</button>' + 
                    '<button id="accclose" class="last">关闭</button>' + 
                '</div>';

            $('body').prepend(buttonHtml);
            $('#acctoolbar').css('left', $('#wrapper').offset().left + 1);
            $('#wrapper').css('padding-top', '31px');

			//ie6 style hack
            if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
                $('#acctoolbar').css('position', 'absolute');
                $(window).scroll(function(){
                    $('#acctoolbar').css('top', $(window).scrollTop());
                })
            }

            // 设置内容宽度
            var contentWidth = storage.getCookie('content_width');
            if(contentWidth) {
                setContentWidth(contentWidth);
            }
			
			//text zoom in
            $('#textin').click(function() {
                var s = parseInt($('body').css('font-size').replace('px', ''), 10);
                s = s + 2;
                $('body').css('font-size', s + 'px');
            });
			//text zoom out
            $('#textout').click(function(){
                var s = parseInt($('body').css('font-size').replace('px', ''), 10);
                s = s - 2;
                $('body').css('font-size', s + 'px');
            });

            $('#width_high').click(function() {
                setContentWidth(0);

                storage.setCookie('content_width', 0, 360);
            });

            $('#width_normal').click(function() {
                setContentWidth(1);

                storage.setCookie('content_width', 1, 360);
            });

            $('#width_low').click(function() {
                setContentWidth(2);

                storage.setCookie('content_width', 2, 360);
            });
			
			//guide lines
            $('#guides').click(function(){
                if ($('#guides_horiz')[0]) {
                    $('#guides_horiz,#guides_verti').remove();
                    $('body').unbind("mousemove");
                    if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
                        $(window).unbind("resize");
                    }
                }
                else {
                    $('body').append('<div id="guides_horiz"></div><div id="guides_verti"></div>').mousemove(function(pos){
                        //console.info($(document).scrollTop());
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
            });

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

            $('#should_read').click(function() {
                speaker.read_enabled = !speaker.read_enabled;
                
                updateStatus();
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

    function updateStatus() {
        if(speaker.read_enabled) {
            $('#should_read').html('关闭声音朗读');
            storage.setCookie('read_the_words', 1, 360);
        } else {
            $('#should_read').html('开启声音朗读');
            storage.eraseCookie('read_the_words');
        }
    }
});
