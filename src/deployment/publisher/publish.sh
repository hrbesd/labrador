
DIR=`basedir $0`
source $DIR/*.conf

# Publish the entire software
mkdir $DIR/labrador
source $DIR/*.dirs
source $DIR/*.butts
rsync -av --copy-links $DIR/labrador/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$VERSION/

# Create symbol links
mkdir $DIR/labrador/bin
source $DIR/*.links
rsync -av $DIR/labrador/bin/ $UPDATE_LOGIN@$UPDATE_SERVER:~/labrador/$VERSION/bin/

rm -r $DIR/labrador