test -z "$1" && fail "You must specify a module to run."
if test "$2" == "for"; then
	test -n "$3" || fail "You must specify a site ID after 'for'."
	SITE_ID=$3
else
	locate_site
fi

source $DIR/../common/launch.sh
log "Launching $1 for $SITE_ID...\n"
launch_module $1 $SITE_ID
