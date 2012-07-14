#!/bin/bash

CONSOLE_VERSION="Labrador Admin Console Version Alpha 3"

# Finding the real script thru links
# SELF=$0
# while true; do
# 	DIR=`dirname $SELF`
# 	SELF=`readlink $SELF`
# 	test -z "$SELF" && break
# done

# My solution sucks, so copy a clip from stackoverflow.com
# Finding location of the actual script:
SOURCE="${BASH_SOURCE[0]}"
DIR="$( dirname "$SOURCE" )"
while [ -h "$SOURCE" ]
do 
	SOURCE="$(readlink "$SOURCE")"
	[[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
	DIR="$( cd -P "$( dirname "$SOURCE"  )" && pwd )"
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

# source $DIR/utils/common.sh
source ~/.profile

if test ! -f $LABRADOR_CONFIG; then
	echo "Error: config file not found." >&2
	exit 1
else
	source $LABRADOR_CONFIG
fi

append_console_log()
{
	CONSOLE_LOG=$LABRADOR_LOG/console.log
	printf "`date '+%Y-%m-%d %H:%M:%S'`\t$*\n" >> $CONSOLE_LOG
}

log() 
{ 
	printf "$*\n"
	append_console_log "$*"
}

log_item()
{ 
	printf "\t * $*\n"
	append_console_log " * $*"
}

log_error()
{
	printf "Error: $*\n"
	append_console_log "[Error]\t$*"
}

fail()
{
	printf "\nError: $*\n" >&2
	append_console_log "$*"
	exit 1
}

get_siteroot()
{
	while test ! -f '.siteroot'
	do
		cd ..
		test "`pwd`" == '/' && break
	done
	test `pwd` != '/' && printf `pwd`
}

site_exists()
{
	test -d $LABRADOR_SITES/$1 && test -f $LABRADOR_SITES/$1/.site_root
}

locate_site()
{
	if test -n "$SITE_ID" && site_exists $SITE_ID; then
		export SITE_ROOT=$LABRADOR_SITES/$SITE_ID
	else
		export SITE_ROOT=`get_siteroot`
		test -z "$SITE_ROOT" && SITE_ID="" && fail "Not in a site repository."
		export SITE_ID=`basename $SITE_ROOT`
	fi
	export SITE_CONF=$SITE_ROOT/config/site.conf
}

usage()
{
	printf "\nUsage:\n \tlab <command> [<arguments>]\n" >&2
	printf "\nSupported lab commands are:\n"
	for i in `ls $DIR/commands/*.sh`
	do
		printf "\t`basename $i .sh`\n"
	done
}

if test -z "$*" -o "$1" == "help" -o "$1" == "usage"; then
	usage
	exit 0
else
	COMMAND=$1
	shift
	SITE_ID=$1
	COMMAND_SCRIPT="$DIR/commands/$COMMAND.sh"
	test ! -f $COMMAND_SCRIPT && fail "Command not exists: $COMMAND. See 'lab help'."
	source $COMMAND_SCRIPT $*
fi