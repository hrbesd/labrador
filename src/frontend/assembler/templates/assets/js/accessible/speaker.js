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
speaker.url = "http://localhost:12321";
speaker.audioPlaying = false;
speaker.read_enabled = true;

// 伪成员方法

// 朗读方法，唯一的对外接口
speaker.speak = function (text)
{
    if(!speaker.read_enabled) {
        return;
    }
    var pl = new SOAPClientParameters();
    pl.add("string", text);
    SOAPClient.simpleSoapRequest(speaker.url, "http://example.com/tts_service", "text2speech", pl);
    // tests if the audio file exists
    var audioURL = "http://localhost:2000/" + faultylabs.MD5(text) + ".m4a";
    speaker.checkSoundExists(audioURL);
}

// 检查声音在服务端是否已经被创建
// 如果已经被创建，那么直接播放；否则，1秒之后再试
speaker.checkSoundExists = function (audioURL) {
    $.ajax({
        url:audioURL,
        type:'HEAD',
        error: function()
        {
            setTimeout(checkSoundExists(audioURL), 1000);
        },
        success: function()
        {
            speaker.sayWord(audioURL);
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
    } else {
        speaker.read_enabled = false;
    }
}

// 根据语音播放选项决定语音播放状态
speaker.updateSpeakerStatus = function() {
    if(speaker.read_enabled) {
        storage.setCookie('read_the_words', 1, 360);
    } else {
        storage.eraseCookie('read_the_words');
    }
}