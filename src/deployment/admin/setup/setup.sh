#!/bin/bash

DIR=`dirname $0`
source $DIR/*.conf
test -z "$LABRADOR_ROOT" && echo "Bad config file." && exit 1

test -d $LABRADOR_ROOT || ( mkdir $LABRADOR_ROOT && echo "Created $LABRADOR_ROOT." )

echo "Updating bin..."
test -d $LABRADOR_BIN || ( mkdir $LABRADOR_BIN && echo "Created $LABRADOR_BIN." )
rsync -av $DEV_SERVER_URL/bin/ $LABRADOR_BIN/
if test $? -eq 0; then
	echo "Successfully done."
else
	echo "Failed!"
fi

# Ensure bin inside path
grep $LABRADOR_BIN ~/.profile >/dev/null
test $? -eq 0 || echo '$PATH='$LABRADOR_BIN':$PATH' >>~/.profile && echo "Updated .profile!"

# etc
test -d $LABRADOR_ETC || ( mkdir $LABRADOR_ETC && echo "Created $LABRADOR_ETC." )
test -d $LABRADOR_TEMPLETS || ( mkdir $LABRADOR_TEMPLETS && echo "Created $LABRADOR_TEMPLETS." )

echo "Updating etc..."
rsync -av -r --copy-links $DEV_SERVER_URL/etc/ $LABRADOR_ETC/
test $? -eq 0 && echo "Sucessfully done." || echo "Failed!"

test -d $LABRADOR_LOG || ( mkdir $LABRADOR_LOG && echo "Created $LABRADOR_LOG." )
test -d $LABRADOR_SITES || ( mkdir $LABRADOR_SITES && echo "Created $LABRADOR_SITES." )
test -d $LABRADOR_BUTTS || ( mkdir $LABRADOR_BUTTS && echo "Created $LABRADOR_BUTTS." )

echo "Updating butts..."
rsync -av -r --copy-links $DEV_SERVER_URL/butts/ $LABRADOR_BUTTS/
test $? -eq 0 && echo "Sucessfully done." || echo "Failed!"

echo "Setup completed."
echo

