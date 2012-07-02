# 安装、配置、更新 Labrador

*草稿*

*不完整*

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

user name labrador
uid 1111