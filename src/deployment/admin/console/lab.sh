#!/bin/bash

# Finding the real script thru links
SELF=$0
while true; do
	DIR=`dirname $SELF`
	SELF=`readlink $SELF`
	test -z "$SELF" && break
done

source $DIR/utils/common.sh

DEFAULT_COMMAND="info"

function usage
{
	printf "Usage:\n \t lab <command> [<arguments>]\n \t lab -e <command>\n \t lab -l\n"
	local exit_status=$1
	test -z "$exit_status" && exit_status=1 
	exit $exit_status
}

while getopts "elh" OPTION
do
    case $OPTION in
        e)  MODE="EDIT"
            ;;
        l)  MODE="LIST"
            ;;
		h)	usage 0
			;;
        ?)  usage 1
            ;;
    esac
done
shift $(($OPTIND-1))

test -n "$MODE" || MODE="EXEC"

COMMAND="$1"
shift

[ "$COMMAND" == "help" ] && usage 0
test -z "$COMMAND" && COMMAND=$DEFAULT_COMMAND

COMMAND_SCRIPT="$DIR/commands/$COMMAND.sh"

if [[ "$MODE" == "EXEC" || "$MODE" == "EDIT" ]]; then
	if test ! -f $COMMAND_SCRIPT; then
		echo "`basename $0`: command not exists: $COMMAND_SCRIPT"
		exit 2
	fi	
fi

case $MODE in
	"EDIT") $EDITOR $COMMAND_SCRIPT ;;
	"LIST") for i in `ls $DIR/commands/*.sh`; do printf "`basename $i .sh`\n"; done ;;
	"EXEC") source $COMMAND_SCRIPT $* ;;
	?)		usage ;;
esac

