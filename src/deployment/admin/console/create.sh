source `basedir $0`/utils/common.sh

usage()
{
	echo "$0: <id> <host>" >&2
	exit 1	
}

test -n "$1" || test -n "$2" && usage

cp -r $LABRADOR_TEMPLETS $LABRADOR_SITES/$1
