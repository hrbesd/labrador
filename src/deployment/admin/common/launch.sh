launch_module()
{
	test $# -eq 2 || return 1
	local module_name=$1
	local site_id=$2
	local prev_module=
	local need_webroot=
	local need_stylesheets=
	case $module_name in
		generator)
			BUTT="$GENERATOR_PATH"
			;;
		spider)
			BUTT="$SPIDER_PATH"
			;;
		parser)
			BUTT="$PARSER_PATH"
			prev_module=spider
			;;
		reactor)
			BUTT="$REACTOR_PATH"
			prev_module=parser
			;;
		assembler)
			BUTT="$ASSEMBLER_PATH"
			prev_module=reactor
			need_webroot="YES"
			need_stylesheets="YES"
			;;
		*)
			echo "Unknown module name." >&2
			return 1
			;;
	esac
	
	local site_root=$LABRADOR_SITES/$site_id
	local site_conf=$site_root/config/site.conf
	local conf_dir=$LABRADOR_ROOT/etc

	arguments="--site-config=$site_conf \
		--worker-dir=$site_root/workers/$module_name \
		--shared-dir=$site_root/workers/shared \
		--config-dir=$conf_dir/$module_name \
		--rule-dir=$site_root/rules/$module_name \
		--log-file=$site_root/logs/$module_name"
	test -n "$prev_module" && arguments="$arguments --source-dir=$site_root/workers/$prev_module"
	test -n "$need_webroot" && arguments="$arguments --webroot-dir=$site_root/webroot"
	test -n "$need_stylesheets" && arguments="$arguments --stylesheet-dir=$site_root/stylesheets"
	$BUTT $arguments
}
