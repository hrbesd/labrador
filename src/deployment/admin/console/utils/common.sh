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

CONSOLE_LOG=$LABRADOR_LOG/console.log
append_console_log()
{
	printf "`date '+%Y-%m-%d %H:%M:%S'`\t$*\n" >> $CONSOLE_LOG
}

log() { printf "$*\n"; append_console_log "$*"}
log_item { printf "\t * $*\n"; append_console_log " * $*"}
log_error { printf "Error: $*\n" append_console_log "[Error]\t$*"}
fail { printf "\nError: $*\n" >&2; append_console_log "$*"; exit 1 }

test -z "$EDITOR" && export EDITOR=nano # Or vi?

site_exists()
{
	test -d $LABRADOR_SITES/$1 && test -f $LABRADOR_SITES/$1/.site_root
}

SITE_ID=$1
locate_site()
{
	if test -n "$SITE_ID" && site_exists $SITE_ID; then
		export SITE_ROOT=$LABRADOR_SITES/$SITE_ID
	else
		export SITE_ROOT=`get_siteroot`
		test -z "$SITE_ROOT" && fail "Not in a site repository."
		export SITE_ID=`basename $SITE_ROOT`
	fi
	export SITE_CONF=$SITE_ROOT/config/site.conf
}