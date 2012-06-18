# Translate Cache Web Service

## 目的
由于Google Translate是一个付费服务，因此，如果每次都对同样的文本请求翻译会产生不必要的费用，可能会造成经济损失。因此，设计并实现一套简单的翻译结果的缓存。当客户端发送请求的时候，Web Service首先查找缓存文件，如果查找得到了结果，就直接将结果返回给客户端；如果缓存不存在，那么Web Service再去请求Google，将得到的翻译结果缓存，再将结果返回给客户端。

## 功能
- 翻译： 中文->英语

## 请求连接
- 端口为9999
- URL: ```http://<server host name>:9999/translate/<lang>/内容```
- 对于英语：lang为en

## 实现
- Web Service使用Python编写
- 服务器模块暂时使用轻量级的Bottle模块，连接：[Bottle Py](http://bottlepy.org/docs/dev/)
- 获取的翻译结果使用文件夹的形式存储
    * 将翻译的内容进行Hash
    * 利用Hash结果的前6位构建文件夹
    * 每一条翻译结果对应一个文件，这个文件名的前6位正好在之前构建的文件夹中
    * 如果已经命中，就不再调用Google服务，否则，请求。