echo "You must use this script in a repo!"
read -p "Where is the setup.sh script?" REPLY
test -f $REPLY || ( echo "File not found."; exit 1)

cat $REPLY | head -50 | tail -39 | sed -e '/^#/d' >directories.conf

cat addresses.conf >labrador.conf
cat directories.conf >>labrador.conf
cat paths.conf >>labrador.conf

echo "labrador.conf generated." 