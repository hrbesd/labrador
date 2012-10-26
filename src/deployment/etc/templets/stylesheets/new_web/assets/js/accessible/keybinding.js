/**
 * 键盘绑定模块
 *
 * 由于系统中需要大量使用快捷键，如果静态的绑定，那么当有大量键值绑定的时候，就非常不便于查找、修改。
 * 因此决定设计一套动态绑定的方案，使用单独的js作为配置文件，动态的实现按键与函数功能的实现。
 *
 * “包”名： keybinding
 *
 * Author: Void Main
 */
 var keybinding = {};

// 处理对应的按键时间的函数
// 参数：event - document.keyDown函数中的对应参数
// 首先判断是否已经按下了ctrl+shift键，之后再根据keybinding.config里面的内容进行按键功能匹配
keybinding.processKeyEvent = function(event) {
	//if (event.ctrlKey && event.shiftKey) {
	if (event.altKey) {
		//alt+~ 复位页面
		//alt+1 标准视图
		//alt+2 黑夜视图
		//alt+3 高对比度视图
		//alt+[ 增加页宽
		//alt+] 减少页宽
		//alt+' 复位页宽
		//alt+; 放大镜
		//alt+\ 辅助线
		bindingResult = keybinding.alt.config[event.keyCode];
		if (bindingResult) {
			action[bindingResult]();
		}
	}
	if(event.ctrlKey){
		//ctrl+{ 增加字体
		//ctrl+} 减少字体
		//ctrl+' 复位字体
		bindingResult = keybinding.ctrl.config[event.keyCode];
		if (bindingResult) {
			action[bindingResult]();
		}
	}
	if(event.shiftKey){
		//shift+{ 增加行距
		//shift+} 减少行距
		//shift+' 复位行距
		bindingResult = keybinding.shift.config[event.keyCode];
		if (bindingResult) {
			action[bindingResult](); 
		}
	}

}