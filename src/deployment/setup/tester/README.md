# 安装、配置、更新 Labrador

*草稿*

*不完整*

## 第一次安装

### 管理员

以具有 `sudo` 权限的用户登录，根据开发方的说明获得并运行安装脚本：

```
$ ./setup.sh --config-sshd --create-user --install-keys
```

### 操作员

操作员使用上面脚本新创建的 labrador 账户登录，运行脚本继续完成安装：

```
~/.setup.sh --make-dirs --modify-env --sync-bin --sync-etc
```

测试员可以在 `setup.sh` 后面插入 `--go-dev` 之类的参数，设置更新通道。

在运营服务器上谨慎使用 `--go-unstable` 和 `--go-dev` 参数。如果误用，使用 `--go-stable` 参数重置更新通道。

## 更新

### 程序更新

```
$ ./setup.sh -sync-bin
```

更新内容：

- `butts` 目录下的程序
- `bin` 目录下的链接

### 配置更新

```
$ ./setup.sh -sync-bin
```

更新内容：

- 软件配置
- 新网站模板

除非特殊说明，通常可以只更新程序，不更新配置。

## Usage (临时文档)

```
Usage

	`basename $0` [options]
	
Options

	--check-env		Check environment for essential modules
	
	User labrador only:

	--make-dirs		Create required directories
	--sync-bin		Sync executable programs
	--sync-etc		Sync settings
	--modify-env	Modify environment variables
	
	Root only:

	--config-sshd	Modify the config file of sshd
	--create-user	Create the labrador user
	--install-keys	Install ssh keys, user labrador must exist
	
Note

	Check the first few lines of this script for basic settings.

```

## 约定

- 用户名: labrador
- 用户组: users
- uid: 1111