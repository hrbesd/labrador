/**
 * 定义网页特殊UI元素
 * 
 * 特殊元素包括：
 *     半透明层（用来显示帮助文档、翻译结果）
 *     放大镜层（用来放大某些链接内容）
 * 
 * “包”名： ui
 *
 * Author: Void Main
 */

var ui = {};

// 在屏幕左上角开始startX, startY的位置，生成一个宽度为width，高度为height的遮盖层
// 里面填充innerHtml对应的内容
// 参数：startX - 相对于左上角的X偏移
//      startY - 相对于左上角的Y偏移
//      width - 遮罩层的宽度
//      height - 遮罩层的高度
//      innerHTML - 内部填充的元素内容
ui.seperateLayer = function(startX, startY, width, height, innerHTML) {
	var shelterColor = "Black";
	var shelterAlp = 75;
	var layerDiv = "<div id='half_opacity_layer' style='width:" + width 
	    + ";height:" + height 
	    + ";background-color:" + shelterColor 
	    + ";filter:alpha(opacity=" + shelterAlp 
	    + ");position:absolute;left:0;top:0;right:100%;bottom:100%;'></div>";
    $("body").append(layerDiv);
    
    var contentDiv = "<div id='layer_content' style='border:solid 25px white;position:absolute;left:" + startX 
    	+ "px;top:" + startY + "px;overflow:hidden;margin:0 auto;z-index=1;'>" 
    	+ innerHTML + "</div>";
    $("#half_opacity_layer").before(contentDiv);   
    $("#half_opacity_layer").show().bind("click", function() { 
    	$(this).remove();
    	$("#layer_content").remove().prev().remove();
    });  
}