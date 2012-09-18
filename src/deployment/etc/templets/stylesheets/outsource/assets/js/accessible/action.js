/**
 * Action指令
 *
 * 提供各个action，调用不同package提供的功能
 * 实际提供了一个抽象层结构，将需要参数的方法实例化
 * 取消需要的参数，这样方便快捷键绑定的设计
 * 有一个基本原则：在这个包中的函数，全部没有参数
 *
 * “包”名： action
 *
 * Author: Void Main
 */
var action = {};

//标准
action.changeToStandardTheme = function() {
	basic.changeTheme.changeToStandard();
}
//夜视
action.changeToDarkTheme = function() {
	basic.changeTheme.changeToDark();
}
//高对比度
action.changeToHightContrastTheme = function() {
	basic.changeTheme.chageToHightContrast();
}
//文字放大 
action.increaseFontSize = function() {
	basic.fontSize.increaseFont();
}
//文字缩小
action.decreaseFontSize = function() {
	basic.fontSize.decreaseFont();
}
//增加页宽
action.increaseScreenWidth = function() {
	basic.screenWidth.increaseScreenWidth();
}
//减少页宽
action.decreaseScreenWidth = function() {
	basic.screenWidth.decreaseScreenWidth();
}
//增加行宽
action.increaseLineHeight = function() {
	basic.lineHeight.increaseHeight();
}
//减少行宽
action.decreaseLineHeight = function() {
	basic.lineHeight.decreaseHeight();
}
//显示放大镜
var bMagnifier = true;
action.showMagnifier = function() {
	if(bMagnifier){
		basic.magnifier.showMagnifier();
		bMagnifier=false;
	}else{
		basic.magnifier.hideMagnifier();
		bMagnifier=true;
	}
}
//隐藏放大镜
action.hideMagnifier = function() {
	basic.magnifier.hideMagnifier();
}
//放大镜
action.toggleMagnifier = function() {
	basic.magnifier.toggleMagnifier();
}
//辅助线
action.toggleGuides = function() {
	basic.guides.toggleGuides();
}

//显示帮助
action.showHelp = function() {
	alert("播放语音帮助");
	basic.help.showHelp();
}
//隐藏帮助
action.hideHelp = function() {
	basic.help.hideHelp();
}
//朗读
action.toggleSpeak = function () {
	alert("朗读文字");
	speaker.read_enabled = !speaker.read_enabled;
    speaker.updateSpeakerStatus();
}
//横竖工具栏切换
action.toggleStyle = function() {
	basic.styleSwitcher.toggleStyle();
}
