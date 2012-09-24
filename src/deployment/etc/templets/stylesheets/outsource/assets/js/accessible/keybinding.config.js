/**
 * 键盘绑定配置文件
 *
 * 键盘绑定是一系列可以更改的键值对，其中键是键盘的按键编码，值是对应函数的名称。
 * 这里的按键已经默认按下了ctrl+shift两个键，不再对这两个键有别的需求。
 * 如果后续需要扩展，再进行添加
 * 
 * “包”名： keybinding.config
 *
 * Author: Void Main
 */

keybinding.config = {
	'83':'accessible',
	'192':'changeToStandardTheme',//标准试图
	'49':'changeToDarkTheme',//夜视	
	'50':'changeToHightContrastTheme',//高对比度
	'51':'increaseFontSize',////文字放大 
	'52':'decreaseFontSize',//文字缩小
	'53':'increaseScreenWidth',//增加页宽
	'54':'decreaseScreenWidth',//减少页宽
	'55':'increaseLineHeight',//增加行宽
	'56':'decreaseLineHeight',//减少行宽
	'57':'showMagnifier',//显示放大镜//'48':'hideMagnifier',//隐藏放大镜
	//'48':'toggleMagnifier',//放大镜
	'48':'toggleGuides',//辅助线
	'191':'showHelp',//显示帮助
	'a':'hideHelp',//隐藏帮助
	'a':'toggleStyle',//横竖工具栏切换
	'a':'toggleSpeak'//朗读
	
};