/**
 * 工具条的简单实现，提供了4个功能：放大、缩小、辅助线、对比度翻转；
 * 目前没有开发的功能：预定样式表、放大镜、语音播放
 * @version 0.1
 */
var url = "http://localhost:12321";
var audioPlaying = false;
var read_enabled;

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
  
	var accessible_enable = false;
  
    if (getCookie('accessible') == 1) {
        accessible();
    }

    // toggle read
    if (getCookie('read_the_words') == 1) {
        read_enabled = true;
    } else {
        read_enabled = false;
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
                read_enabled = !read_enabled;
                
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
                eraseCookie('accessible');
            });
			
			//save cookie
			setCookie('accessible', 1, 360);
        }
        return false;
    }

    function updateStatus() {
        if(read_enabled) {
            $('#should_read').html('关闭声音朗读');
            setCookie('read_the_words', 1, 360);
        } else {
            $('#should_read').html('开启声音朗读');
            eraseCookie('read_the_words');
        }
    }
});

function speak(text)
{
    if(!read_enabled) {
        return;
    }
    var pl = new SOAPClientParameters();
    pl.add("string", text);
    SOAPClient.simpleSoapRequest(url, "http://example.com/tts_service", "text2speech", pl);
    // tests if the audio file exists
    var audioURL = "http://localhost:2000/" + faultylabs.MD5(text) + ".m4a";
    checkSoundExists(audioURL);
}

function checkSoundExists(audioURL) {
    $.ajax({
        url:audioURL,
        type:'HEAD',
        error: function()
        {
            setTimeout(checkSoundExists(audioURL), 1000);
        },
        success: function()
        {
            sayWord(audioURL);
        }
    });   
}

function audioFinished() {
    audioPlaying = false;
}

function sayWord(audioURL) {
    if(!audioPlaying) {
        audioPlaying = true;
        var soundPlayer = new Audio(audioURL);
        soundPlayer.addEventListener('ended', audioFinished);
        soundPlayer.play();
    }    
}

function doTranslate(text) {
    var translateURL = "https://www.googleapis.com/language/translate/v2?key=AIzaSyDaSjttIQryVZn8sqUkVmx227SsiWiYzC8&source=zh-CN&target=en&q=" + escape(text);
    $.ajax({
        url:translateURL,
        type:'GET',
        error: function()
        {
        },
        success: function(data)
        {
            alert(data.data.translations[0].translatedText);
        }
    }); 
}
