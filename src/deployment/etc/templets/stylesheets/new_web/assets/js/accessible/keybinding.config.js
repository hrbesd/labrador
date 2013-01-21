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
keybinding.alt={};
keybinding.alt.config={
	/*
	'192':'restPage',
	'49':'changeToStandardTheme',//标准试图
	'50':'changeToDarkTheme',//夜视	
	'51':'changeToHightContrastTheme',//高对比度
	'219':'increaseScreenWidth',//增加页宽
	'221':'decreaseScreenWidth',//减少页宽
	'222':'resetScreenWidth',//还原页宽
	'186':'toggleMagnifier',//放大镜
	'220':'toggleGuides'//辅助线
	*/
	'192':'restPage',
	'49':'changeToStandardTheme',//标准试图
	'50':'changeToDarkTheme',//夜视	
	'51':'changeToHightContrastTheme',//夜视	
	'219':'batch_read',//自动朗读
	'221':'point_read',//文字缩小
	'222':'resetFontSize',//文字还原
	'186':'increaseFontSize',//文字放大
	'220':'decreaseFontSize'//文字缩小
}
keybinding.ctrl={};
keybinding.ctrl.config={
	'219':'increaseScreenWidth',//增加页宽
	'221':'decreaseScreenWidth',//减少页宽
	'222':'resetScreenWidth'//还原页宽
};
keybinding.shift={};
keybinding.shift.config={
	'219':'increaseLineHeight',//增加行宽 
	'221':'decreaseLineHeight',//减少行宽
	'222':'resetLineHeight'//还原行宽
}
keybinding.config = {
	'83':'accessible',
	'49':'changeToStandardTheme',//标准试图192
	'50':'changeToDarkTheme',//夜视	
	'51':'changeToHightContrastTheme'//高对比度
	/*
	'57':'showMagnifier',//显示放大镜//'48':'hideMagnifier',//隐藏放大镜
	'191':'showHelp',//显示帮助
	'a':'hideHelp',//隐藏帮助
	'a':'toggleStyle',//横竖工具栏切换
	'a':'toggleSpeak'//朗读
	*/
};
