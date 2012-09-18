
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
keybinding.processKeyEvent = function (event) {
	//if (event.ctrlKey && event.shiftKey) {
	if (event.altKey) {
		bindingResult = keybinding.config[event.keyCode];
		if (bindingResult) {
			//bindingResult();
			action[bindingResult](); // 最后的括号才是真正的调用方法
		}
	}
};

