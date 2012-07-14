#!/bin/bash

usage()
{
	printf "Usage: `basename $0` <name_of_release>\n\n" >&2
	exit 3
}

test -z "$*" && usage

# Finding the real script thru links
SELF=$0
while true; do
    DIR=`dirname $SELF`
    SELF=`readlink $SELF`
    test -z "$SELF" && break
done

PROMOTER_PATH=$DIR/promote.sh

DIR=$DIR/releases/$1
test ! -d $DIR && printf "Config dir of this release was not found:\n \t$DIR\n\n" >&2 && exit 1

source $DIR/*.conf

test -d $TMP_DIR && rm -r $TMP_DIR
# Publish the entire software
echo "Making temp dir for syncing ..."
mkdir $TMP_DIR
echo "Making dirs ..."
for f in $DIR/*.dirs; do source $f; done
echo "Putting butts in ..."
for f in $DIR/*.files; do source $f; done
echo "Kicking asses ..."
rsync -av --copy-links --delete $TMP_DIR/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/

# Create symbol links
echo "Creating links for executables ..."
mkdir $TMP_DIR/bin
for f in $DIR/*.links; do source $f; done
rsync -av --delete $TMP_DIR/bin/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/bin/

# And don not forget the promoter
echo "Updating promote.sh ..."
rsync -av $PROMOTER_PATH $UPDATE_LOGIN@$UPDATE_SERVER:~

# rm -r $DIR/$TMP_DIR

# Leave the message
echo "Leaving a message ..."
ssh $UPDATE_LOGIN@$UPDATE_SERVER "echo $MESSAGE >/home/$UPDATE_LOGIN/labrador/$CHANNEL/readme.txt"
echo "All done."
