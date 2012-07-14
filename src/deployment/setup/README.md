# 安装、配置、更新 Labrador

*草稿*

*不完整*

## 服务器初始化

### 查看操作系统环境

```
uname -v
```

确保有 `Ubuntu` 字样

### 建立管理员用户

```
# adduser esd --ingroup admin --shell /bin/bash
```

管理员的默认密码由开发方提供。

## 第一次安装

### 管理员

不要使用 `root`，以具有 `sudo` 权限的用户登录，根据开发方的说明获得并运行安装脚本：

默认安装方式：

```
$ wget -q -O- http://get.yunmd.info/install | bash
```

#### 运行之前

如果开发方有特别说明，按说明使用文本编辑器修改脚本最前的参数；否则不用修改脚本。

#### 安装基本软件包

```
$ sudo ./setup.sh --install-dev
```

#### 自动配置 OpenSSH Server

```
$ sudo ./setup.sh --config-sshd
```

#### 检查软件配置

```
$ ./setup.sh --check-env
```

确保全部测试通过再进行下一步操作。

#### 创建用户

**提示** 进行如下操作之前请通过 Email 等方式获取用户 `updater` 的密码。

```
$ sudo ./setup.sh --create-tester sue
```
将创建一位名为 sue 的测试员。

```
$ sudo ./setup.sh --create-user labrador
```
将创建一位操作员 labrador。

**注意** 操作员的默认用户名为 labrador，在上面的命令中可以省略。

被创建的用户使用密钥登录。密钥名为 `esd_rsa`，由管理员分发。

### 安装软件

用户第一次登录后运行：

```
$ ./setup.sh --check-env
```
确保操作环境满足需求。


#### 第一次安装

先检查环境变量：

```
$ ./setup.sh --modify-env
```

如果提示更新了PATH，需要重新登录修改才能立刻生效。

开始安装：

```
$ ./setup.sh --make-dirs --sync-bin --sync-etc
```

测试员可以在 `setup.sh` 后面插入 `--go-dev` 之类的参数，设置更新通道。

在运营服务器上谨慎使用 `--go-unstable` 和 `--go-dev` 参数。如果误用，使用 `--go-stable` 参数重置更新通道。

## 更新软件

### 测试员更新

#### 更新通道

测试员选择更新通道为：

- dev，对应命令 `--go-dev`
- unstable， 对应命令 `--go-unstable`

#### 只更新程序

如果想保留配置，可以只更新程序

```
$ ./setup.sh -sync-bin
```

涉及的更新内容：

- `butts` 目录下的程序
- `bin` 目录下的链接

#### 只更新配置

如果想保留目前版本的程序，可以只更新配置

```
$ ./setup.sh -sync-etc
```

涉及的更新内容：

- 软件配置
- 新网站模板

#### 备注

* 除非特殊说明，通常可以只更新程序，不更新配置。
* 一个测试员可以有多个测试账号，对应不同的程序或配置。

### 操作员更新

*基本同测试员更新*

不同之处：

- 只能选择 stable 通道更新，默认不用修改
- 如无特殊情况，一台服务器只可以有一个操作员，一个操作员只能有一个账号
- 默认用户名 labrador

