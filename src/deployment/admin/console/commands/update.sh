if test -z "$*"; then
	SITE_ROOT=`get_siteroot`
	if test -d "$SITE_ROOT"; then
		echo "Error: At least one site must be specified." >&2
		exit 1
	else
		`grep 'ID=' $SITE_ROOT/config/site.conf`
		$SCHEDULER $ID
	fi
else
	if test "$1" == "all"; then
		$SCHEDULER_PATH
	else
		$SCHEDULER_PATH $*
	fi
fi


