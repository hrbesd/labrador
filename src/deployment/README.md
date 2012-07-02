# Labrador 服务器部署攻略

*草稿*

*不完整*

## 操作系统

Development Server 和 Production Server 统一采用 Ubuntu 11.10 系统。

## Development Server

### 初始化

#### 基本软件包

`apt-get install …`

- openssh-server
- apache2
- vim

#### 端口开通/映射

`80`
`22`

### 用户

#### GoF

- 主要用途
	* 开发方同步 `~/repo`

- 如何建立
	* 手工建立
	
- 使用者
	* 开发方

- 权限
	* 用 `labrador` key 登录
	* 禁止密码登录
	* `sudo-er`
	
- 可以做什么？
	* 同步 Github repo
	* daily-build
	* 可以更新repo，但不推荐
	
- 不可以做什么?
	* 运行测试

#### updater
	
- 主要用途
	* setup
	* sync

- 如何建立
	* 手工建立
	
- 使用者
	* 开发方
	* 运行方

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

#### labrador

- 主要用途
	* 模拟运营

- 如何建立
	* 安装脚本建立
	
- 使用者
	* 开发方

- 权限
	* 用 `labrador` key 登录
	* 禁止密码登录
	* 非 `sudo-er`
	
- 可以做什么？
	* 首次安装
	* 日常更新
	* 模拟运营
	
- 不可以做什么?
	* 扩大权限

**Note:** 尽量与 Production Server 的程序和配置一致
	
## Production Server

### 初始化

#### 基本软件包

`apt-get install …`

- openssh-server
- apache2
- vim

#### 端口开通/映射

`80`
`22`
`2222`
`22222`

#### 安装配置 Labrador

* 通过开发方提供的指示，运行安装脚本。
* 当前操作用户有时需要是 `root` 或者有 `sudo` 权限

满足以上条件，安装脚本会自动把新的服务器初始化成 Production Server.

对于已经运营的 Production Server，参考 [Setup 文档](./admin/setup/README.md) 。

#### 用户

- 安装系统的 `admin` 用户
	* 任何用户名都可以
	* `sudo-er`

- `labrador` 运营方日常工作用户
	* 此用户通过安装脚本自动建立和初始化
	* 禁止 `sudo`
	* 从 `updater` 用户复制 ssh key-pair

## 参考

- [Console 文档](./admin/console/README.md)
- [Setup 文档](./admin/setup/README.md)