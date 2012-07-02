err()
{
	echo "$0: required arguments not found." >&2
	exit 1	
}

test -z "$1" || test -z "$2" && err

cp -r $LABRADOR_TEMPLETS $LABRADOR_SITES/$1
# Updating config
SITE_CONFIG=$LABRADOR_SITES/$1/config/site.conf
sed -e "s/^ID=.*/ID=$1/" -i $SITE_CONFIG
sed -e "s/^HOST=.*/HOST=$2/" -i $SITE_CONFIG

echo "Site '$1' created."
# echo "TODO: Add DNS record in DNSPOD and modify config of Apache."
../utils/add_virtualhost.sh $1 $LABRADOR_SITES/$1/webroot
../utils/addDNSRecord.py $1 $HOST_PUBLIC_IP
