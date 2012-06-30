# Labrador 服务器部署攻略

## 操作系统

Development Server 和 Production Server 统一采用 Ubuntu 11.10 系统。

## Development Server

### 初始化

#### 基本软件包

`apt-get install …`

- openssh-server
- apache2
- vim

### 用户

- `adduser GoF` 开发者，可以 `sudo`，禁止密码登录
	* 同步 Github repo
	* daily-build
	
- `adduser updater` 运营方远程登录，通过 `ssh` 更新
	* Symbol link 指向 `GoF` 的 repo 和生成文件
	
- `labrador` 模拟运营方；供开发方路演和测试
	* 此用户通过安装脚本建立和初始化
	* 尽量与 Production Server 的程序和配置一致
	

## Production Server

### 初始化

#### 基本软件包

`apt-get install …`

- openssh-server
- apache2
- vim

#### 安装配置 Labrador

通过开发方提供的指示，运行安装脚本。

### 用户

- `labrador` 运营方日常工作用户
	* 此用户通过安装脚本建立和初始化
