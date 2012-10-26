#!/bin/bash

EMAIL='admin@yunmd.info'
DOMAIN='yunmd.info'
VIRTUALHOST_ROOT='/etc/apache2/sites-available'

ERROR_NOPERMISSON='你没有权限运行该脚本，请使用sudo运行！'
ERROR_NOHOST='未填写主机名'
ERROR_NOWEBROOT='未填写站点所在目录'
ERROR_HOSTEXIST='该主机已存在，请重新选择主机'
ERROR_WEBROOTEXIST='该网站目录已存在，请重新确认'
ERROR_CREATEHOST='创建主机文件错误'
ERROR_ADDHOST='添加虚拟主机错误'
ERROR_ARGS='缺少参数'

INFO_USAGE='Usage:add_virtualhost.sh hostname webroot'
INFO_HOSTNAME='请输入该网站的名称:(例如 harbin,该名称将作为目录名)'
INFO_WEBROOT='请输入网站所在目录'
INFO_CREATEHOST='成功创建主机文件'
INFO_ADDHOST='成功添加虚拟主机!'
INFO_CREATESITE='成功创建虚拟主机'

# Check the  privilillge

if [ "$(whoami)" != 'root' ]; then
        echo $ERROR_NOPERMISSION
        exit 1;
fi

hostname=$1
webroot=$2
echo $hostname
# Get hostname & webroot from args
if [ $# -lt 2 ];then
	echo $ERROR_ARGS
	echo $INFO_USAGE
	exit 1
fi


if [ "$hostname" = "" ]
then
    echo $ERROR_NOHOST
    exit
fi
	 
if [ "$webroot" = "" ]
then
    echo $ERROR_NOWEBROOT
    exit
fi

virtualhost=${VIRTUALHOST_ROOT}/${hostname}
docroot=${webroot}/${hostname}
# Modified by zhf
#docroot=${webroot}

domainname=${hostname}.${DOMAIN}
#Check the hostname file and webroot dir
if [ -e $virtualhost ];then
    echo $virtualhost
    echo $ERROR_HOSTEXIST
    exit
fi

if [ -d $docroot ]; then
    echo $docroot
    echo $ERROR_WEBROOTEXIST
    exit
fi


if ! touch $virtualhost
then
    echo $ERROR_CREATEHOST
    exit
else
    echo $INFO_CREATEHOST
fi

if ! echo "<VirtualHost *:80>
ServerAdmin $EMAIL
ServerName $domainname
DocumentRoot $docroot
<Directory />
AllowOverride All
</Directory>
<Directory $docroot>
AllowOverride All
</Directory>
ErrorLog /var/log/apache2/$hostname
LogLevel error
CustomLog /var/log/apache2/$hostname custom
</VirtualHost>" > $VIRTUALHOST_ROOT/$hostname

then 
    echo $ERROR_ADDHOST
    exit
else 
    echo $INFO_ADDHOST
fi

mkdir $docroot
chmod 755 $docroot
#enable the virtual host with a2ensite
cd ${VIRTUALHOST_ROOT}
/usr/sbin/a2ensite $hostname
/etc/init.d/apache2 reload

echo $INFO_CREATESITE 
