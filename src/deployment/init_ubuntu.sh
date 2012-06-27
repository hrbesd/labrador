#!/bin/bash

# This script is supposed to run on an ubuntu server

# Re-write public key
# Cliff Woo's Public Key
echo 'ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA1HorRRq7OGM5iK4jnP09X/WsPm6JXSfjhRH5kR1yWOOe3W4B28xoDc6g2xy+lSrXRaVMrfy3WQSKQhGgnEnNEvW2noAR2t/Yhd0rBnGONvB02uujmlhFl6J9HJfvO3LagQi5kjMt3Y62AjGUROkMmeAwHwM3gYNbWDGgS99OSWdXoyhIArZIDTsFXfx3Yt+TZnLPeXb8WFFPNlEnNJfmWQj4CFCdBjEsh+PFPBUiLCWkjDpE0/bqZr+r/o2P8qAdM99ryBIup+zMJJ0UPuGQBgbnTp+aEwGf94US7yAL29SY1YC8Uwr5eh0s/NE0Y2pWC0HyKDf9jY94B40sISfQHw== id_rsa.pub' >/root/.ssh/authorized_keys
chmod 600 /root/.ssh/authorized_keys

function nag
{
	echo " * `basename $0`: $1"
}

# In case of no ssh, Installing openssh
nag 'Installing openssh'
apt-get -y install openssh-server openssh-client

SSHD_CONFIG_FILE=/etc/ssh/sshd_config

echo " * path is: $PATH" >>/root/startup.log
echo " * sshd config file is: $SSHD_CONFIG_FILE" >>/root/startup.log

function sshd_config_append
{
	echo "=> entering sshd_config_append. arguments is: $*" >>/root/startup.log
	echo "$1" | /usr/bin/tee -a $SSHD_CONFIG_FILE > /dev/null
	# echo "$1" >> $SSHD_CONFIG_FILE
	echo "<= leaving sshd_config_append. status = $?" >>/root/startup.log

}

function add_sshd_port
{
	echo "=> entering add_sshd_port. Arguments is $*:" >> /root/startup.log
	for i in $*
	do
		/bin/grep "^Port $i\b" $SSHD_CONFIG_FILE > /dev/null
		if (($? != 0)); then
			sshd_config_append ""
			sshd_config_append "# Open Ports"
			sshd_config_append "Port $i"
			SSHD_CHANGED="YES"
		else
			echo " * Port $i on remote server is already open." >>/root/startup.log
		fi
	done		
	echo "<= leaving add_sshd_port. status = $?" >>/root/startup.log
}

function add_ssh_option
{	
	echo "=> entering add_ssh_option. Arguments is $*" >>/root/startup.log
	# grep "^$1"  $SSHD_CONFIG_FILE > /dev/null
	# (( $? == 0 )) && 
	# Delete existing options
	/bin/sed -i -e "/^$1\ /d" $SSHD_CONFIG_FILE
	sshd_config_append "$1 $2"
	echo " * Updated sshd_config with option: $1 $2." >>/root/startup.log
	SSHD_CHANGED="YES"
	echo "<= leaving add_ssh_option. status = $?" >>/root/startup.log
}

echo "## before ssh options" >>/root/startup.log
add_sshd_port 22 2222 22222
add_ssh_option MaxSessions 100
add_ssh_option TCPKeepAlive no
add_ssh_option ClientAliveCountMax 3
add_ssh_option ClientAliveInterval 10
add_ssh_option Compression yes
add_ssh_option AddressFamily inet
add_ssh_option PermitRootLogin yes

# add_ssh_option LogLevel DEBUG
echo "## end ssh options" >>/root/startup.log

echo "## before restarting sshd" >>/root/startup.log
if [ -n "$SSHD_CHANGED" ]; then
	echo "Restarting sshd ..." >>/root/startup.log
	service ssh restart
fi
echo "## end restarting sshd" >>/root/startup.log

echo 'PS1=[Labrator] $PS1' >> ~/.bashrc

# Zhang Hongfeng's IP
echo 'alias p="ping -c 5 221.212.68.225"' >> ~/.bashrc

useradd -m -g users labrator
mkdir /home/labrator/.ssh
cp /root/.ssh/authorized_keys /home/labrator/.ssh/
chmod 600 /home/labrator/.ssh/authorized_keys
chown labrator:users /home/labrator/.ssh/authorized_keys
chmod 700 /home/labrator/.ssh
chown labrator:users /home/labrator/.ssh

# Reverse a big guy for speedtest to ESD
truncate -s 10M /root/speedtest.bin

# No need to reboot
