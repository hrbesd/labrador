# Labrador Scheduler Spec

## 被调度的模块顺序

* Spider
* Parser
* Reactor
* Assembler

## 参数和环境变量

* 脚本或程序被`CRON`调用，可能没有Login Shell中的环境变量
* 脚本被以绝对路径直接调用，需要自己指定解释器
* 脚本和程序被调用时都是symbolic links

### 参数

* `--site-config=<dir/file>` 当前网站的配置文件
* `--source-dir=<dir>` 作为输入的目录
* `--worker-dir=<dir>` 本模块的工作目录
* `--shared-dir=<dir>` 模块间共享目录，最后一个需要文件的模块负责删除文件
* `--webroot-dir=<dir>` 当前网站的Web Server的根目录
* `--config-dir=<dir>` 配置文件目录；各自模块指定自己的配置文件；开发者编辑
* `--rule-dir=<dir>` 规则目录；各自模块指定自己的规则文件；运营方可编辑
* `--log-file=<dir/file>` 本模块的日志文件

#### 注意
* 以上目录和文件保证存在，私有配置和规则文件模块自己负责检查。
* 空目录中可能有placeholder。

#### 参数中不包括

- 脚本或程序实际文件所在位置（可以添加Working Directory参数）

## 日志

每个模块每次被调用前调度器自己会留下日志。

## 异常

* 不管时间频率如何，全局只有一个调度程序可以运行
* 整个流程如果没有成功完成，下次不会自动运行
* 可以手动清除相应的Flag（程序内定义）

## 已知问题

* 无法指定网站被更新的顺序
* 固定每日自动更新（可以手动更新）
* 配置文件中的时间段暂时被忽略
