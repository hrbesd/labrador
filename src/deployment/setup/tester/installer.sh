UPDATER_HOST="get.yunmd.info" # You have to verify this!


# Check if sudo is available
sudo -S true < /dev/null &>/dev/null

if test $? -ne 0; then
	echo "You must be a sudo-er to continue installation." >&2
	exit 1
fi

cd ~
test -f setup && rm setup
wget $UPDATER_HOST"/setup"
chmod +x ~/setup
echo
echo

#read -p "Would you like to install the required development pakage now? (Y/n) "

#if test "$REPLY" != 'n'; then
#	sudo ~/setup --install-dev --check-env
#else
	echo "Your setup program is downloaded and installed as '~/setup'."
	echo "If you are install the software for the first time, run 'sudo ~/setup --install-dev --check-env'"
	echo "Type './setup.sh help' for help or check out the documents."
#fi
echo
