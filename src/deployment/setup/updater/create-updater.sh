test `id -u` -ne 0 && echo "Root only. Switch to root or use 'sudo'." && exit 1

USERNAME="updater"
SSH_KEY=~/.ssh/esd_rsa
ADMIN_PUB_KEY=~/.ssh/labrador_rsa.pub

test -n "`getent passwd $USERNAME`" && printf "User already exists.\n" && exit 1
test ! -f $SSH_KEY && printf "SSH key $SSH_KEY not found.\n" && exit 1
test ! -f $ADMIN_PUB_KEY && printf "SSH public key $ADMIN_PUB_KEY not found.\n" && exit 1

echo "Adding user updater ..."
useradd -g users --create-home $USERNAME

SSH_DIR=/home/$USERNAME/.ssh

mkdir $SSH_DIR
chmod 700 $SSH_DIR
cp $SSH_KEY $SSH_DIR
cp $SSH_KEY.pub $SSH_DIR
chmod 600 $SSH_DIR/`basename $SSH_KEY`
chmod 600 $SSH_DIR/`basename $SSH_KEY`".pub"
cat $SSH_KEY".pub" > $SSH_DIR/authorized_keys
cat $ADMIN_PUB_KEY >> $SSH_DIR/authorized_keys
chown -R updater:users $SSH_DIR

echo "User 'updater' created."
echo "To set the password for this user now, use 'sudo passwd updater'."
