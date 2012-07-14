test $# -eq 2 || fail "required arguments not found."

cp -r $LABRADOR_TEMPLETS $LABRADOR_SITES/$1
# Updating config
SITE_CONFIG=$LABRADOR_SITES/$1/config/site.conf
sed -e "s/^ID=.*/ID=$1/" -i $SITE_CONFIG
sed -e "s/^HOST=.*/HOST=$2/" -i $SITE_CONFIG

echo "Site '$1' created."

# Add DNS record in DNSPOD and modify config of Apache.
../utils/add_virtualhost.sh $1 $LABRADOR_SITES/$1/webroot
test $? -eq 0 && log "Virtual host added in Apache."

test -z "$HOST_PUBLIC_IP" && fail "Public IP not set. Check config file."
../utils/addDNSRecord.py $1 $HOST_PUBLIC_IP
test $? -eq 0 && log "DNS record modified."
