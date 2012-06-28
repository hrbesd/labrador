SITE_ROOT=`get_siteroot`

if test -z "$SITE_ROOT"; then
	echo "Error: Not in a site repo." >&2
	exit 1
fi

if test -d $SITE_ROOT; then
	# Backup site config
	cp $SITE_ROOT/config/site.conf /tmp/
	rm -rf $SITE_ROOT
	cp -r $LABRADOR_TEMPLETS $SITE_ROOT
	cp /tmp/site.conf $SITE_ROOT/config/
	
	echo "Site reset."
fi
