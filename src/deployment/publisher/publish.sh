
DIR=`basename $0`
source $DIR/*.conf

# Publish the entire software
mkdir $DIR/labrador
source $DIR/*.dirs
source $DIR/*.butts
rsync -av --copy-links $DIR/labrador/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/

# Create symbol links
mkdir $DIR/labrador/bin
source $DIR/*.links
rsync -av $DIR/labrador/bin/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$CHANNEL/bin/

# rm -r $DIR/labrador

# Leave the message
ssh $UPDATE_LOGIN@$UPDATE_SERVER echo $MESSAGE >/home/labrador/$CHANNEL/readme.txt
