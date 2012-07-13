test `id -u` -ne 0 && echo "Root only. Switch to root or use 'sudo'." && exit 1

USERNAME="updater"

check()
{
	getent passwd $USERNAME >/dev/null
}

fail()
{
	printf "Error: $*\n"
	exit 1
}

case $1 in
	help|usage)
		echo "Usage: `basename $0` create | check | remove" >&2
		exit 1
		;;
	remove)
		check
		test $? -eq 0 || fail "User not found."
		deluser --remove-home $USERNAME
		test $? && echo "User sucessfully removed."
		exit 0
		;;
	create)
		check
		test $? -eq 0 && fail "User already exists."
		echo "Adding user updater ..."
		# and go on ...
		;;
	check)
		check
		test $? -eq 0 || printf "No "
		printf "user exists.\n"
		exit 0
		;;
	*)
		echo "Try 'help'." >&2
		exit 1
		;;
esac

# Adding user

SSH_KEY=~/.ssh/esd_rsa
ADMIN_PUB_KEY=~/.ssh/labrador_rsa.pub

test ! -f $SSH_KEY && printf "SSH key $SSH_KEY not found.\n" && exit 1
test ! -f $ADMIN_PUB_KEY && printf "SSH public key $ADMIN_PUB_KEY not found.\n" && exit 1

useradd -g users --create-home --shell /bin/bash $USERNAME

SSH_DIR=/home/$USERNAME/.ssh
LAB_DIR=/home/$USERNAME/labrador
SSH_CONFIG=$SSH_DIR/config

mkdir $LAB_DIR
chmod 700 $LAB_DIR
mkdir $LAB_DIR/dev $LAB_DIR/unstable $LAB_DIR/stable
mkdir $SSH_DIR
chmod 700 $SSH_DIR
cp $SSH_KEY $SSH_DIR
cp $SSH_KEY.pub $SSH_DIR
cat $SSH_KEY".pub" > $SSH_DIR/authorized_keys
cat $ADMIN_PUB_KEY >> $SSH_DIR/authorized_keys
echo "Host *" > $SSH_CONFIG
echo "IdentityFile ~/.ssh/`basename $SSH_KEY`" >>$SSH_CONFIG
echo "StrictHostKeyChecking no" >>$SSH_CONFIG
echo "UserKnownHostsFile=/dev/null" >>$SSH_CONFIG

chmod 600 $SSH_DIR/*
chown -R updater:users /home/$USERNAME/*
chown -R updater:users /home/$USERNAME/.ssh

echo "User $USERNAME created."
echo "To set the password for this user now, use 'sudo passwd updater'."
