#!/bin/bash

DIR=`basedir $0`
source $DIR/*.conf
test -z "$LABRADOR" && echo "Bad config file." && exit 1

test -d $LABRADOR_ROOT || mkdir $LABRADOR_ROOT && echo "Created root directory at $LABRADOR_ROOT."

echo "Updating executables..."
test -d $BIN_DIR || mkdir $BIN_DIR && echo "Created $BIN_DIR."
rsync -av --copy-links $DEV_SERVER_URL/bin $BIN_DIR
if $? -eq 0; then
	echo "Successfully done."
else
	echo "Failed!"
fi

# Ensure bin inside path
grep $BIN_DIR ~/.profile >/dev/null
test $? -eq 0 || echo "$PATH=$BIN_DIR:$PATH" >>~/.profile && echo "Updated .profile!"

# Config
test -d $ETC_DIR || mkdir $ETC_DIR && echo "Created $ETC_DIR."
cp $DIR/*.conf $ETC_DIR/
# Templets
test -d $TEMPLET_DIR || mkdir $TEMPLET_DIR && echo "Created $TEMPLET_DIR."

echo "Updating templets..."
rsync -av --copy-links $DEV_SERVER_URL/templets $TEMPLET_DIR
test $? -eq 0 && echo "Sucessfully done." || echo "Failed!"

test -d $LOG_DIR || mkdir $LOG_DIR && echo "Created $LOG_DIR."

echo "Setup completed."
echo

