UPDATER_HOST="219.217.227.82" # You have to verify this!


# Check if sudo is available
sudo -S true < /dev/null &>/dev/null

if test $? -ne 0; then
	echo "You must be a sudo-er to continue." >&2
	exit 1
fi

cd ~
wget $UPDATER_HOST"/setup.sh"
chmod +x ~/setup.sh
echo
echo

sudo ~/setup.sh --install-dev --check-env