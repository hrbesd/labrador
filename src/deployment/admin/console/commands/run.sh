test "$2" == "for" && test -n "$3" && ID=$3
if test -z "$ID"; then
	SITE_ROOT=`get_siteroot`
	test -z "$SITE_ROOT" && echo "Not in a site repo." > &2 && exit 1
else
	SITE_ROOT=$LABRADOR_SITES/$ID
fi

source ../../common/launch.sh
launch_module $1 $3
