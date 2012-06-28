if test -z "$*"; then
	echo "Error: At least one site must be specified." >&2
	exit 1
fi

$SCHEDULER_PATH $*
