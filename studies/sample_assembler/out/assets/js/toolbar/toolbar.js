/**
 * 工具条的简单实现，提供了4个功能：放大、缩小、辅助线、对比度翻转；
 * 目前没有开发的功能：预定样式表、放大镜、语音播放
 * @version 0.1
 */
jQuery(document).ready(function(){
    
	//cookie fucntions
    function setCookie(name, value, days){
        if (days) {
            var date = new Date();
            date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
            var expires = "; expires=" + date.toGMTString();
        }
        else 
            var expires = "";
        document.cookie = name + "=" + value + expires + "; path=/";
    }
    function getCookie(name){
        var nameEQ = name + "=";
        var ca = document.cookie.split(';');
        for (var i = 0; i < ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0) == ' ') 
                c = c.substring(1, c.length);
            if (c.indexOf(nameEQ) == 0) 
                return c.substring(nameEQ.length, c.length);
        }
        return null;
    }
    function eraseCookie(name){
        setCookie(name, "", -1);
    }
  
	var accessible_enable = false;
	//high contrast
	function acc_highcontrast(){
	
        if (accessible_enable == false || $('#highcontrast').hasClass('high')) {
			eraseCookie('accessible_highcontrast');
            $('body').css('background', '#FFFFFF');
            $('body').css('color', '#333333');
            $('a').css('color', '#000000');
            $('button').css('color', '#000000');
            $('#highcontrast').removeClass('high').text('高对比度');
			$('ul li').css('color', '#ffffff');
        }
        else {
			setCookie('accessible_highcontrast', 1, 360);
            $('body').css('background', '#000000');
            $('a, button, body').css('color', '#FFFFFF');
            $('#highcontrast').addClass('high').text('还原对比度');
        }
	}
  
    if (getCookie('accessible') == 1) {
        accessible();
    }
	
    if (getCookie('accessible_textmode') == 1) {
        accessible();
		acc_textmode();
    }
	if (getCookie('accessible_highcontrast') == 1) {
		accessible();
		acc_highcontrast();
    }
	
	// ctrl + shirt + S  high contrast
	$(document).keydown(function(event){
        if (event.ctrlKey && event.shiftKey && event.keyCode == '83') {
            accessible();
			acc_highcontrast();
        }
    });
    
	//attach click event accessible 
	$('#accessible').click(accessible);
	
    function accessible(){
        if (!$('#acctoolbar')[0]) {
			accessible_enable = true;
			
		    var link = document.createElement('LINK');
		    link.setAttribute('rel','stylesheet');
		    link.setAttribute('type','text/css');
		    link.setAttribute('href','css/accessible.css');
		    document.getElementsByTagName('head')[0].appendChild(link);
			
			//initial buttons
            $('body').prepend('<div id="acctoolbar"><button id="textin">文字放大</button><button id="textout">文字缩小</button><button id="highcontrast">高度对比</button><button id="guides">辅助线</button><button id="accclose" class="last" >关闭</button></div>');
            $('#acctoolbar').css('left', $('#wrapper').offset().left + 1);
            $('#wrapper').css('padding-top', '31px');
			//ie6 style hack
            if ($.browser.msie && $.browser.version.substr(0, 1) < 7) {
                $('#acctoolbar').css('position', 'absolute');
                $(window).scroll(function(){
                    $('#acctoolbar').css('top', $(window).scrollTop());
                })
            }
			
			//high contrast
			$('#highcontrast').click(acc_highcontrast);
			
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
            
			//close button
            $('#accclose').click(function(){
				accessible_enable = false;
				
                acc_highcontrast();  
				          
                if (parseInt($('body').css('font-size').replace('px', ''), 10) != 12) {
                    $('body').css('font-size', '12px');
                }
                
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
                eraseCookie('accessible');
            });
			
			//save cookie
			setCookie('accessible', 1, 360);
        }
        return false;
    }
});