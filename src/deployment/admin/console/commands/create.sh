test $# -eq 2 || fail "required arguments not found."

cp -r $LABRADOR_ETC/templets $LABRADOR_SITES/$1
# Updating config
SITE_CONFIG=$LABRADOR_SITES/$1/config/site.conf
sed -e "s/^ID=.*/ID=$1/" -i $SITE_CONFIG
sed -e "s/^HOST=.*/HOST=$2/" -i $SITE_CONFIG

echo "Site '$1' created."

# Add DNS record in DNSPOD and modify config of Apache.
sudo $DIR/utils/add_virtualhost.sh $1 $LABRADOR_SITES/$1/webroot
test $? -eq 0 && log "Virtual host added in Apache."

if test -z "$HOST_PUBLIC_IP"; then
	ETH0_IP="`/sbin/ifconfig eth0 | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}'`"
	read -p "Public IP not in config file. Use '$ETH0_IP' for DNS record? (Y/n) "
	test "$REPLY" != "n" && HOST_PUBLIC_IP=$ETH0_IP
fi

test -n "$HOST_PUBLIC_IP" && $DIR/utils/addDNSRecord.py $1 $HOST_PUBLIC_IP
test $? -eq 0 && log "DNS record sucessfully modified."
