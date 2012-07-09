if test "$1" == "all"; then
	$SCHEDULER_PATH
else
	SITES=$*
	if test -z "$*"; then
		fail_unless_in_repo
		SITES=$SITE_ID
	fi
	$SCHEDULER_PATH $SITES
fi


