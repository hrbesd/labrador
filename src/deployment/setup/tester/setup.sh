#!/bin/bash

# Known bug: if the varible exists but pointing to a wrong location, it wont be updated.

# Note: this script must be run as root
# Resersed
# Resersed
# Resersed
# Resersed

# *IMPORTANT* This line must be the 11th line because this another script parse this one!

# =======================================================================================
# Config these variables.
# =======================================================================================

UPDATER_LOGIN=updater
UPDATER_ROOT=/home/$UPDATER_LOGIN/labrador
UPDATER_BIN=bin
UPDATER_ETC=etc
UPDATER_BUTTS=butts
UPDATER_SITES=sites
UPDATER_LOG=log
UPDATER_HOST="219.217.227.82" # You have to verify this!

LABRADOR_ROOT=~/labrador
LABRADOR_BIN=$LABRADOR_ROOT/$UPDATER_BIN
LABRADOR_ETC=$LABRADOR_ROOT/$UPDATER_ETC
LABRADOR_SITES=$LABRADOR_ROOT/$UPDATER_SITES
LABRADOR_BUTTS=$LABRADOR_ROOT/$UPDATER_BUTTS
LABRADOR_LOG=$LABRADOR_ROOT/$UPDATER_LOG

UPDATE_CHANNEL_FILE=~/.labrador-update-channel
# Resersed
# Resersed
# Resersed
# Resersed
DEFAULT_TESTER_NAME=tester
DEFAULT_USER_NAME=labrador
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed
# Resersed

# *IMPORTANT* This line must be the 51th line because this another script parse this one!
#
# =======================================================================================
# Do not modify lines below unless you are a developer!
# =======================================================================================

# Variables
UPDATER_URL=$UPDATER_LOGIN@$UPDATER_HOST:$UPDATER_ROOT
#DIR=`dirname $0`
SSHD_CONFIG_FILE=/etc/ssh/sshd_config
UPDATE_CHANNEL="stable"
test -f $UPDATE_CHANNEL_FILE && UPDATE_CHANNEL="`cat $UPDATE_CHANNEL_FILE`"

usage()
{
	printf "
	
Usage

	`basename $0` [options]
	
Options

	--check-env		Check environment for essential modules
	
	User and tester only:

	--make-dirs		Create required directories
	--sync-bin		Sync executable programs
	--sync-etc		Sync settings
	--modify-env	Modify environment variables
	--go-stable		Update through the stable channel
	--go-unstable	Update through the unstable channel
	--go-dev		Update through the dev channel

	Root only:

	--config-sshd	Modify the config file of sshd
	--create-user	Create an operating user
	--create-tester	Create a tester
	--install-dev	Install development modules
	
Note

	Check the first few lines of this script for basic settings.

"
}

log()
{
	printf "$*\n"
}

log_item() 
{
	printf "\t * $*\n"
}

log_error() 
{
	printf "Error: $*\n"
}

fail() 
{
	printf "\nError: $*\n"
	exit 1
}

root_or_fail()
{
	# Check if current user is root
	if test `id -u` -ne 0; then
		printf "\nYou must be root to use option: $*\n"; exit 1 
	fi
}

user_or_fail()
{
	# Check if current user is labrador
	if test `id -u` -eq 0; then
		printf "\nYou must be a user to use option: $*\n"; exit 1 
	fi
}

sshd_config_append()
{
	echo "$1" | /usr/bin/tee -a $SSHD_CONFIG_FILE > /dev/null
}

add_sshd_port()
{
	for i in $*
	do
		/bin/grep "^Port $i\b" $SSHD_CONFIG_FILE > /dev/null
		if (($? != 0)); then
			sshd_config_append ""
			sshd_config_append "# Open Ports"
			sshd_config_append "Port $i"
			SSHD_CHANGED="YES"
		else
			log "Port $i on remote server is already open."
		fi
	done
}

add_ssh_option()
{
	/bin/sed -i -e "/^$1\ /d" $SSHD_CONFIG_FILE
	sshd_config_append "$1 $2"
	log "Updated sshd_config with option: $1 $2."
	SSHD_CHANGED="YES"
}

check_ssh_server()
{
	if ! test -x /usr/sbin/sshd; then
		log_error "[X] SSH server not installed."
		return 1
	fi
	log_item "SSH server detected."
	test -f /var/run/sshd.pid || log_item "\t but sshd not started."
}

check_web_server()
{
	if test ! -x /usr/sbin/apache2; then
		log_item "[X] Web server not installed."
		return 1
	fi
	log_item "Web server detected."
	test -f /var/run/apache2.pid || log_item "\t but sshd not started."
}

check_bash_version()
{
	if [[ -n "${BASH_VERSION:-}" ]] &&
		(( 65536 * ${BASH_VERSINFO[0]} + 256 * ${BASH_VERSINFO[1]} + ${BASH_VERSINFO[2]} < 197145 ))
	then
		log_item "[X] BASH 3.2.25 or higher required."
		return 1
	fi
	log_item "You have bash $BASH_VERSION, which is okay."
}

check_python_version()
{
	test -z "`which python`" && log_item "Python not detected." && return 1
	
	python -c 'import sys; sys.exit(sys.version_info.major * sys.version_info.minor - 14)'
	if test $? -eq 0; then
		log_item "Your python is okay."
	else
		log_item "[X] Python 2.7 required."
		return 1
	fi
}

check_rsync_version()
{
	# Do we really require rsync 3?
	if test ! -x /usr/bin/rsync; then
		log_item "[X] rsync not installed."
		return 1
	fi
	log_item "rsync detected."
	test -f /var/run/rsync.pid || log_item "\t but service not started, which is acceptable."
}

set_update_channel()
{
	echo "$*" >$UPDATE_CHANNEL_FILE
	log "Update channel changed to [$*]."
	return 0
}

create_user()
{
	local username="$1"
	getent passwd $username >/dev/null
	if test $? -eq 0; then
		fail "User $username already exists."
	else
		if test "$username" == "$DEFAULT_USER_NAME"; then
			/usr/sbin/useradd -m -s /bin/bash -g users labrator --uid 1111
		else
			/usr/sbin/useradd -m -s /bin/bash -g users $username
		fi
		
		# Share this script with user
		local script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
		local script_path=$script_dir"/`basename $0`"
		chmod 755 $script_path
		ln -s $script_path /home/$username/"`basename $0`"
		log "User $username sucessfully created."

		log "Logging on update server to continue to install keys ..."

		mkdir /home/$username/.ssh
		/usr/bin/scp $UPDATER_LOGIN@$UPDATER_HOST:~/.ssh/* /home/$username/.ssh
		test $? -eq 0 || return 1
		chown -R $username:users /home/$username/.ssh
		chmod 700 /home/$username/.ssh
		chmod 600 /home/$username/.ssh/*
		log "SSH keys installed."
	fi
}

install_dev()
{
	
}
# log "Begin setting up ...\n"

# Parse CLI arguments.
while test -n "$*";
do
	token="$1"
	shift
	case "$token" in
		--check-env)
			failed=1
			log "\nCheck environment ..." 
			check_ssh_server || failed=0
			check_web_server || failed=0
			check_bash_version || failed=0
			check_python_version || failed=0
			check_rsync_version || failed=0
			test $failed -eq 0 && log_error "Not all tests passed." || log_item "All tests passed. :)"
			;;

		--sync-etc)
			user_or_fail "$token"
			log "\nUpdating settings ..."
			rsync -av --delete --copy-links $UPDATER_URL/$UPDATE_CHANNEL/etc/ $LABRADOR_ETC/
			test $? -eq 0 && log_item "Sucessfully done." || log_error "Failed!"
			;;

		--sync-bin)
			user_or_fail "$token"
			log "\nUpdating programs ..."
			rsync -av --delete --copy-links $UPDATER_URL/$UPDATE_CHANNEL/$UPDATER_BUTTS/ $LABRADOR_BUTTS/
			test $? -eq 0 && rsync -av --delete $UPDATER_URL/$UPDATE_CHANNEL/$UPDATER_BIN/ $LABRADOR_BIN/
			test $? -eq 0 && log_item "Sucessfully done." || log_error "Update failed!"
			;;

		--make-dirs)
			user_or_fail "$token"
			false
			test -d $LABRADOR_ROOT || mkdir $LABRADOR_ROOT
			test -d $LABRADOR_LOG || mkdir $LABRADOR_LOG
			test -d $LABRADOR_SITES || mkdir $LABRADOR_SITES
			test $? -eq 0 && log "Directories created."
			;;

		--go-stable)
			user_or_fail "$token"
			UPDATE_CHANNEL="stable"
			set_update_channel $UPDATE_CHANNEL
			;;

		--go-unstable)
			user_or_fail "$token"
			UPDATE_CHANNEL="unstable"
			set_update_channel $UPDATE_CHANNEL
			;;

		--go-dev)
			user_or_fail "$token"
			UPDATE_CHANNEL="dev"
			set_update_channel $UPDATE_CHANNEL
			;;

		--modify-env)
			user_or_fail "$token"
			# Ensure bin inside path
			log "\nModifying PATH ..."
			grep $LABRADOR_BIN ~/.profile >/dev/null
			test $? -eq 0 && log_item "Action skipped." || ( echo 'export PATH='$LABRADOR_BIN':$PATH' >>~/.profile && log_item "Updated PATH! To make this change take effect now, log out and log back." )
			
			# Add $LABRADOR_CONFIG to .profile
			#grep "LABRADOR_CONFIG" ~/.profile >/dev/null
			#test $? -eq 0 || ( echo 'LABRADOR_CONFIG='$LABRADOR_ETC'/labrador.conf' >>~/.profile && echo "Added LABRADOR_CONFIG!" )
			;;

		--config-sshd)
			root_or_fail "$token"
			log "\nModifying sshd config ..."
			add_sshd_port 22 2222 22222
			add_ssh_option MaxSessions 100
			add_ssh_option TCPKeepAlive no
			add_ssh_option ClientAliveCountMax 3
			add_ssh_option ClientAliveInterval 10
			add_ssh_option Compression yes
			add_ssh_option AddressFamily inet
			add_ssh_option PermitRootLogin yes

			if [ -n "$SSHD_CHANGED" ]; then
				log_item "Restarting sshd ..."
				/usr/sbin/service ssh restart
				log_item "Done."
			fi
			;;

		--create-tester)
			root_or_fail "$token"
			TESTER_NAME="$1"
			if [[ "$TESTER_NAME" =~ --* ]]; then
				TESTER_NAME="$DEFAULT_TESTER_NAME"
			else
				shift
			fi
			log "Creating tester $TESTER_NAME ..."
			create_user $TESTER_NAME
			echo "unstable" >/home/$TESTER_NAME/.labrador-update-channel
			chown $TESTER_NAME:users /home/$TESTER_NAME/.labrador-update-channel
			;;

		--create-user)
			root_or_fail "$token"
			USER_NAME="$1"
			if [[ "$USER_NAME" =~ --* ]]; then
				USER_NAME=$DEFAULT_USER_NAME
			else
				shift
			fi
			log "Creating user $USER_NAME..."
			create_user $USER_NAME
			;;

		--install-dev)
			root_or_fail "$token"
			log "Refreshing apt cache ...\n\n"
			sleep 1

			apt-get update
			# python2.7-dev: 
			apt-get -y install python2.7-dev
			# python-pip: 
			apt-get -y install python-pip
			# python-dateutil html5lib : 
			easy_install python-dateutil html5lib
			# Amara: 
			easy_install amara
			
			# Ruby 1.8
			apt-get -y install ruby1.8
			# sinatra
			gem install sinatra
			;;

		help|usage|-h|--help|--usage)
			usage
			exit 0
			;;

		*)
			usage
			exit 1
			;;

	esac
done

echo ""
log "Setup completed."
echo ""
