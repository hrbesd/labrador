/**
 * 数据存储模块
 *
 * 提供对cookie操作的接口
 * 目前包括setCookie、getCookie和eraseCookie三个方法
 * “包”名： storage
 *
 * Author: Void Main
 */

var storage = {};

// 设置cookie有效
// 参数：name - cookie名称
//      value - cookie存储的值
//      days - cookie的有效时限
storage.setCookie = function(name, value, days){
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        var expires = "; expires=" + date.toGMTString();
    }
    else {
        var expires = "";
    }
    document.cookie = name + "=" + value + expires + "; path=/";
}

// 根据对应名称获取cookie的值
// 参数：name - cookie名称
storage.getCookie = function(name){
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
    
// 删除cookie内容
// 参数：name - 要删除的cookie的名称
storage.eraseCookie = function(name){
    storage.setCookie(name, "", -1);
}