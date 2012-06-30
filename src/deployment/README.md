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

- `adduser GoF` 开发者
	* `sudo-er`
	* 禁止密码登录
	* 同步 Github repo
	* daily-build
	
- `adduser updater` 运营方远程登录，通过 `ssh` 更新
	* Symbol link 指向 `GoF` 的 repo 和生成文件
	* ssh key-pair 使用 `esd_rsa`
	* `cat ~/.ssh/esd_rsa.pub >>~/.ssh/authorized_keys`
	
- `labrador` 模拟运营方；供开发方路演和测试
	* 此用户通过安装脚本建立和初始化
	* 尽量与 Production Server 的程序和配置一致
	* 从 `updater` 用户复制 ssh key-pair
	
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