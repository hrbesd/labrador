if test "$1" == "--global"; then
	$EDITOR $LABRADOR_ETC/labrador.conf
else
	locate_site
	$EDITOR $SITE_CONF
fi