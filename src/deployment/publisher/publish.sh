#!/bin/bash

# Finding the real script thru links
SELF=$0
while true; do
    DIR=`dirname $SELF`
    SELF=`readlink $SELF`
    test -z "$SELF" && break
done

DIR=$DIR/steps
source $DIR/*.conf

test -d $TMP_DIR && rm -r $TMP_DIR
# Publish the entire software
echo "Making temp dir for syncing ..."
mkdir $TMP_DIR
echo "Making dirs ..."
source $DIR/*.dirs
echo "Putting butts in ..."
source $DIR/*.butts
echo "Kicking asses ..."
rsync -av --copy-links --delete $TMP_DIR/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/

# Create symbol links
echo "Creating links for executables ..."
mkdir $TMP_DIR/bin
source $DIR/*.links
rsync -av --delete $TMP_DIR/bin/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/bin/

# rm -r $DIR/$TMP_DIR

# Leave the message
echo "Leaving a message ..."
ssh $UPDATE_LOGIN@$UPDATE_SERVER "echo $MESSAGE >/home/$UPDATE_LOGIN/labrador/$CHANNEL/readme.txt"
echo "All done."
