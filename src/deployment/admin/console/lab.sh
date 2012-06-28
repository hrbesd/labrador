DIR=`dirname $0`
DEFAULT_COMMAND="show"

function usage
{
	printf "Usage:\n \t ec <command> [<arguments>]\n \t lab -e <command>\n \t ec -l\n"
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

COMMAND_SCRIPT="$DIR/$COMMAND.sh"

if [[ "$MODE" == "EXEC" || "$MODE" == "EDIT" ]]; then
	if test ! -f $COMMAND_SCRIPT; then
		echo "`basename $0`: command not exists: $COMMAND_SCRIPT"
		exit 2
	fi	
fi

case $MODE in
	"EDIT") $EDITOR $COMMAND_SCRIPT ;;
	"LIST") for i in `ls $DIR/*.sh`; do printf "`basename $i .sh`\n"; done ;;
	"EXEC") $COMMAND_SCRIPT $* ;;
	?)		usage ;;
esac

