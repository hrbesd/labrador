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

action.toggleSpeak = function () {
	speaker.read_enabled = !speaker.read_enabled;
    speaker.updateSpeakerStatus();
}

action.increaseScreenWidth = function() {
	basic.screenWidth.increaseScreenWidth();
}

action.decreaseScreenWidth = function() {
	basic.screenWidth.decreaseScreenWidth();
}

action.increaseFontSize = function() {
	basic.fontSize.increaseFont();
}

action.decreaseFontSize = function() {
	basic.fontSize.decreaseFont();
}

action.increaseLineHeight = function() {
	basic.lineHeight.increaseHeight();
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