#!/bin/bash

# Known bug: if the varible exists but pointing to a wrong location, it won't be updated.`

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
UPDATER_ROOT=/home/$UPDATER_LOGIN
UPDATER_BIN=bin
UPDATER_ETC=etc
UPDATER_BUTTS=butts
UPDATER_SITES=sites
UPDATER_LOG=log
UPDATER_HOST=192.168.1.241 # You have to verify this!

LABRADOR_ROOT=~/labrador
LABRADOR_BIN=$LABRADOR/$UPDATER_BIN
LABRADOR_ETC=$LABRADOR/$UPDATER_ETC
LABRADOR_SITES=$LABRADOR/$UPDATER_ROOT
LABRADOR_BUTTS=$LABRADOR/$UPDATER_BUTTS
LABRADOR_LOG=$LABRADOR/$UPDATER_LOG

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

usage()
{
	printf "
	
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

"
}

log() { printf "$*\n" }
log_item { printf "\t * $*\n" }
log_error { printf "Error: $*\n" }
fail { printf "\nError: $*\n"; exit 1 }

root_or_fail()
{
	# Check if current user is root
	if [[ $EUID -ne 0 ]]; then
	fi
	printf "\nYou must be root to use option: $*\n"; exit 1 }
}

user_or_fail()
{
	# Check if current user is labrador
	if [[ $EUID -ne 1111 ]]; then
	fi
	printf "\nYou must be user labrador to use option: $*\n"; exit 1 }
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
	echo "<= leaving add_ssh_option. status = $?" >>/root/startup.log
}

check_ssh_server()
{
	if ! test -x /usr/sbin/sshd; then
		log_error "SSH server not installed."
		return 1
	fi
	log_item "SSH server detected."
	test -f /var/run/sshd.pid || log_item "\t but sshd not started."
}

check_web_server()
{
	if ! test -x /usr/sbin/apache2; then
		log_item "Web server not installed."
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
	  echo "BASH 3.2.25 required."
	  return 1
	fi
	echo "You have bash $BASH_VERSION, which is okay."
}

check_python_version()
{
	test -z "`which python`" && log_item "Python not detected." && return 1
	
	python -c 'import sys; sys.exit(sys.version_info.major * sys.version_info.minor - 14)'
	if test $? -eq 0; then
		log_item "Your python is okay."
	else
		log_item "Python 2.7 required."
		return 1
	fi
}

check_rsync_version()
{
	# Do we really require rsync 3?
	if ! test -x /usr/bin/rsync; then
		log_item "rsync not installed."
		return 1
	fi
	log_item "rsync detected."
	test -f /var/run/rsync.pid || log_item "\t but service not started, which is acceptable."
}

log "Begin setting up ..."

# Parse CLI arguments.
while (( $* > 0 ))
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
			rsync -av --delete --copy-links $DEV_SERVER_URL/etc/ $LABRADOR_ETC/
			test $? -eq 0 && log_item "Sucessfully done." || log_error "Failed!"
			;;
			
		--sync-bin)
			user_or_fail "$token"
			log "\nUpdating programs ..."
			rsync -av --delete --copy-links $UPDATER_URL/$UPDATER_BUTTS/ $LABRADOR_BUTTS/
			test $? -eq 0 && rsync -av --delete $UPDATER_URL/$UPDATER_BUTTS/ $LABRADOR_BIN/
			test $? -eq 0 && log_item "Sucessfully done." || log_error "Update failed!"
			;;
			
		--make-dirs)
			user_or_fail "$token"
			false
			test -d $LABRADOR || mkdir $LABRADOR
			test -d $LABRADOR_LOG || mkdir $LABRADOR_LOG
			test -d $LABRADOR_SITES || mkdir $LABRADOR_SITES
			test $? -eq 0 && log "Directories created."
			;;
			
		--modify-env)
			user_or_fail "$token"
			# Ensure bin inside path
			log "\nModifying PATH ..."
			grep $LABRADOR/bin ~/.profile >/dev/null
			test $? -eq 0 && log_item "Action skipped." || ( echo 'export PATH='$LABRADOR_BIN':$PATH' >>~/.profile && log_item "Updated PATH!" )
			
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
			
		--create-user)
			root_or_fail "$token"
			log "Creating user ..."
			# Per doc, user name and uid is hard-coded
			/usr/sbin/useradd -m -g users labrator --uid 1111
			
			# Prepare dir for ssh
			mkdir /home/labrator/.ssh
			chown labrator:users /home/labrator/.ssh
			chmod 700 /home/labrator/.ssh
			
			# Share this script with user labrador
			chmod 777 $0
			cp $0 /home/labrador/
			log_item "Done."
			;;
			
		--install-keys)
			root_or_fail "$token"
			# Use the same key-par as the updater
			# Yes, user must have updater's password
			/usr/bin/scp $UPDATER_LOGIN@$UPDATER_HOST:~/.ssh 
			# Disable password login
			/usr/bin/passwd -d labrador
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

echo
log "Setup completed."
echo
