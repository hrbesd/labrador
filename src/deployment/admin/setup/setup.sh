#!/bin/bash

DIR=`dirname $0`
source $DIR/*.conf
test -z "$LABRADOR_ROOT" && echo "Bad config file." && exit 1

test -d $LABRADOR_ROOT || ( mkdir $LABRADOR_ROOT && echo "Created $LABRADOR_ROOT" )

echo "Setting up Labrador..."
echo "Updating bin..."
test -d $LABRADOR_BIN || ( mkdir $LABRADOR_BIN && echo "Created $LABRADOR_BIN" )
rsync -av --delete $DEV_SERVER_URL/bin/ $LABRADOR_BIN/
test $? -eq 0 && echo "Successfully done." || echo "Failed!"

# Ensure bin inside path
grep $LABRADOR_BIN ~/.profile >/dev/null
test $? -eq 0 || ( echo '$PATH='$LABRADOR_BIN':$PATH' >>~/.profile && echo "Updated PATH!" )

# etc
test -d $LABRADOR_ETC || ( mkdir $LABRADOR_ETC && echo "Created $LABRADOR_ETC" )
test -d $LABRADOR_TEMPLETS || ( mkdir $LABRADOR_TEMPLETS && echo "Created $LABRADOR_TEMPLETS." )

# Add $LABRADOR_CONFIG to .profile
grep "LABRADOR_CONFIG" ~/.profile >/dev/null
test $? -eq 0 || ( echo 'LABRADOR_CONFIG='$LABRADOR_ETC'/labrador.conf' >>~/.profile && echo "Added LABRADOR_CONFIG!" )
# Known bug: if the varible exists but pointing to a wrong location, it won't be updated.`

echo "Updating etc..."
rsync -av --delete --copy-links $DEV_SERVER_URL/etc/ $LABRADOR_ETC/
test $? -eq 0 && echo "Sucessfully done." || echo "Failed!"

test -d $LABRADOR_LOG || ( mkdir $LABRADOR_LOG && echo "Created $LABRADOR_LOG" )
test -d $LABRADOR_SITES || ( mkdir $LABRADOR_SITES && echo "Created $LABRADOR_SITES" )
test -d $LABRADOR_BUTTS || ( mkdir $LABRADOR_BUTTS && echo "Created $LABRADOR_BUTTS" )

echo "Updating butts..."
rsync -av --delete --copy-links $DEV_SERVER_URL/butts/ $LABRADOR_BUTTS/
test $? -eq 0 && echo "Sucessfully done." || echo "Failed!"

echo "Setup completed."
echo
