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
//点读
action.point_read = function(){
	speaker.pointRead();
}
//连读
action.batch_read = function(){
	if(speaker.bodyTextStatus==true){
		speaker.bodyTextStatus=false;
		speaker.batchRead();
	}
	speaker.batchRead();
}
action.close_read = function(){
	speaker.stop();
}
//语音帮助
action.toggleSpeak = function () {

}

action.increaseScreenWidth = function() {
	basic.screenWidth.increaseScreenWidth();
}
action.resetScreenWidth = function(){
	basic.screenWidth.resetScreenWidth();
}

action.decreaseScreenWidth = function() {
	basic.screenWidth.decreaseScreenWidth();
}

action.increaseFontSize = function() {
	basic.fontSize.increaseFont();
}
action.resetFontSize = function() {
	basic.screenWidth.resetFont();
}

action.decreaseFontSize = function() {
	basic.fontSize.decreaseFont();
}

action.increaseLineHeight = function() {
	basic.lineHeight.increaseHeight();
}

action.resetLineHeight = function() {
	basic.lineHeight.resetLineHeight();
}

action.decreaseLineHeight = function() {
	basic.lineHeight.decreaseHeight();
}

action.changeToStandardTheme = function() {
	basic.changeTheme.changeToStandard();
}

action.changeToDarkTheme = function() {
	basic.changeTheme.changeToDark();
}

action.changeToHightContrastTheme = function() {
	basic.changeTheme.chageToHightContrast();
}

action.toggleGuides = function() {
	basic.guides.toggleGuides();
}

action.toggleMagnifier = function() {
	basic.magnifier.toggleMagnifier();
}

action.showMagnifier = function() {
	basic.magnifier.showMagnifier();
}

action.hideMagnifier = function() {
	basic.magnifier.hideMagnifier();
}

action.showHelp = function() {
	basic.help.showHelp();
}

action.hideHelp = function() {
	basic.help.hideHelp();
}

action.toggleStyle = function() {
	basic.styleSwitcher.toggleStyle();
}
action.restPage = function(){
	basic.resetpage.reset();
}

action.toggleTranslate = function(){
	basic.translator.toggleTranslate();
}
