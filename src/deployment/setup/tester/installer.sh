UPDATER_HOST="get.yunmd.info" # You have to verify this!


# Check if sudo is available
sudo -S true < /dev/null &>/dev/null

if test $? -ne 0; then
	echo "You must be a sudo-er to continue installation." >&2
	exit 1
fi

cd ~
test -f setup.sh && rm setup.sh
wget $UPDATER_HOST"/setup"
chmod +x ~/setup
echo
echo

read -p "Would you like to install the required development pakage now? (Y/n) "

if test "$REPLY" != 'n'; then
	sudo ~/setup --install-dev --check-env
else
	echo "Run setup to continue. If you don not know what to do, type './setup.sh help' or check out the documents."
fi
