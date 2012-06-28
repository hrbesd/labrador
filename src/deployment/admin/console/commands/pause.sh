SITE_ROOT=`get_siteroot`
if test -d $LABRADOR_SITES/$1; then
	touch $LABRADOR_SITES/$1/SITE_DOWN
else
	echo "Error: Site not found." >&2
fi
