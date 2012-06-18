# TTS Web Service原型

### Web Service入口
* server2.rb
* scheduler.rb
* 使用 ```ruby server2.rb```启动服务，端口号 __12321__

### TTS服务
* 任务在```text/```子目录中，按时间排队
* 产品在```audio/```子目录中，也是Web Server的根目录
* 使用```bash tts_worker.sh```启动服务

### Web Server
* 使用```ruby webserver.rb```启动服务
* 使用 __2000__ 端口

### 客户端模拟
* 使用```ruby client.rb```，没有返回结果显示
* ```wget http://<hostname>:2000/<md5hash>.m4a```

### 备注
* 仅在Mac OS X Lion上测试过
* Ruby 1.8.8
* m4a可能只有Safari支持