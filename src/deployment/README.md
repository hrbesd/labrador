# Labrador 服务器部署攻略

*草稿*

*不完整*

*尚未与代码同步*

## 操作系统

服务器统一采用 Ubuntu 11.10 系统。

### 初始化

#### 基本软件包

`apt-get install …`

- openssh-server
- apache2
- vim

#### 端口开通/映射

`80`
`22`

可能为 SSH 服务额外开通 `2222` `22222`

## 应用服务器类型

### Development Server

*“开发服务器”*

- 此类型服务器可以有多个

- 用户
	* GoF **(约定用户名)**

- 主要用途
	* 开发方同步 `~/repo`
	* 向 Update Server 发送更新
	
- 如何建立
	* 开发方手工建立
	
- 使用者
	* 开发方

- 权限
	* 用 `labrador` key 登录
	* 禁止密码登录
	* `sudo-er`
	
- 可以做什么？
	* 同步 Github repo
	* daily-build
	* 特殊情况下在线开发
	
- 不可以做什么?
	* 运行测试
	
### Update Server

*“更新服务器”*

- 此类型服务器只能有一个实例

- 用户
	* updater **(约定用户名)**
	
- 主要用途
	* 通过此服务器初始化 Test Server 和 Production Server
	* 测试主管发布更新

- 如何建立
	* 开发方通过[脚本](./admin/setup/updater/README.md)建立
	
- 使用者
	* Test Server 和 Production Server 的脚本
	* 除了测试主管，无需人登录

- 权限
	* 用 `labrador` 或 `esd` key 登录
	* 可以密码登录
	* 非 `sudo-er`
	
- 可以做什么？
	* 首次安装
	* 更新
	
- 不可以做什么?
	* 运行测试
	* Clone repo

### Test Server

*测试服务器*

- 此类型服务器可以有多个实例

- 用户
	* labrador **(约定用户名)**

- 主要用途
	* 测试软件
	* 模拟运营

- 如何建立
	* 系统管理员通过[安装脚本](./admin/setup/tester/README.md)建立（参考相关文档）
	* 从 Update Server 获得 ssh key-pair
	
- 使用者
	* 开发方或运营方的测试者

- 权限
	* 用 `labrador` key 登录
	* 禁止密码登录
	* 非 `sudo-er`
	
- 可以做什么？
	* 首次安装
	* 日常更新
	* 模拟运营
	
- 不可以做什么?
	* 扩大日常用户的权限

### Production Server

*运营服务器*

- 此类型服务器可以有多个实例

- 用户
	* labrador **(约定用户名)**

- 主要用途
	* 日常运营

- 如何建立
	* 系统管理员通过安装脚本建立（参考相关文档）
	* 从 Update Server 获得 ssh key-pair
	
- 使用者
	* 运营方日常操作人员

- 权限
	* 用 `labrador` key 登录
	* 禁止密码登录
	* 非 `sudo-er`
	
- 可以做什么？
	* 首次安装
	* 日常更新与运营
	
- 不可以做什么?
	* 扩大日常用户的权限

**注意** 此类型服务器默认从 `Stable` 通道获取更新.

### 备注

#### 以下服务器可以共用一个操作系统

- Development Server 
- Update Server
- Test Server

## 部署顺序

1. Developerment Server
2. Update Server
3. Test Server
4. Production Server

## 参考

- [Console 文档](./admin/console/README.md)
- [Updater Setup 文档](./admin/setup/updater/README.md)
- [Tester Setup 文档](./admin/setup/tester/README.md)