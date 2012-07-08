source ~/.profile

if test ! -f $LABRADOR_CONFIG; then
	echo "Error: config file not found."
	exit 1
fi

source $LABRADOR_CONFIG

get_siteroot()
{
	while test ! -f '.siteroot'
 	do
		cd ..
		test "`pwd`" == '/' && break
	done
	test `pwd` != '/' && printf `pwd`
}

log() { printf "$*\n" }
log_item { printf "\t * $*\n" }
log_error { printf "Error: $*\n" }
fail { printf "\nError: $*\n" >&2; exit 1 }

SITE_ROOT=`get_siteroot`
SITE_ID=`basename $SITE_ROOT`

fail_unless_in_repo()
{
	test -z "$SITE_ROOT" && fail "Not in a site repository."
}

fail_unless_site_exists()
{
	local site_id=$1
	test -d $LABRADOR_SITES/$site_id && test -f $LABRADOR_SITES/$site_id/.site_root || fail "Site not exists."
}