/**
 * 语音朗读模块
 *
 * 提供调用后端提供语音朗读部分的功能代码
 * “包”名： speaker
 *
 * Author: Void Main
 */
var speaker = {};

// 伪成员变量
speaker.url = "http://123.165.136.125:8080";
speaker.audioPlaying = false;
speaker.read_enabled = true;

// 伪成员方法

// 朗读方法，唯一的对外接口
speaker.speak = function (text)
{
    if(!speaker.read_enabled) {
        return;
    }
    
    var targetUrl = speaker.url + "/TextToSpeech/webservice/text2Speech/getStatus?jobID=null&text=" + text;
    $.ajax({
        type: 'GET', 
        url: targetUrl,
        success: function(xml) {
            $(xml).find("audio").each(function(){
                var format = $(this).children('format').text();
                var speed = $(this).children('speed').text();
                var sex = $(this).children('voice').children('sex').text();
                var lang = $(this).children('voice').children('lang').text();
                var mp3Url = $(this).children('url').text();
                
                if (format == 'audio/mpeg') {
                    alert(mp3Url);
                    /*var mySound = soundManager.createSound({
                        id: 'textSound',
                        url: mp3Url
                    });
                    mySound.play();*/
                } 
            });
        }        
    });
    
}

// 声音播放完成的回调方法，主要用来设置标志位，标志播放已经完成
speaker.audioFinished = function () {
    speaker.audioPlaying = false;
}

// 真正的发音方法，目前使用HTML5的audio api实现
speaker.sayWord = function (audioURL) {
    if(!speaker.audioPlaying) {
        speaker.audioPlaying = true;
        var soundPlayer = new Audio(audioURL);
        soundPlayer.addEventListener('ended', speaker.audioFinished);
        soundPlayer.play();
    }    
}

// 从cookie中加载语音播放选项
speaker.loadSpeakerStatus = function() {
    // toggle read
    if (storage.getCookie('read_the_words') == 1) {
        speaker.read_enabled = true;
        $('#toggle_speaker').addClass('on');
    } else {
        speaker.read_enabled = false;
        $('#toggle_speaker').removeClass('on');
    }
}

// 根据语音播放选项决定语音播放状态
speaker.updateSpeakerStatus = function() {
    if(speaker.read_enabled) {
        storage.setCookie('read_the_words', 1, 360);
    } else {
        storage.eraseCookie('read_the_words');
    }

    speaker.loadSpeakerStatus();
}