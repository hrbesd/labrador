FLAG=/tmp/LABRADOR_SCHEDULER_RUNNING

log()
{
	printf "`date '+%Y-%m-%d %H:%M:%S'`\t$*\n" >>$LABRADOR_LOG/scheduler.log
}

test -f $FLAG && log "Previous scheduler still running or crashed." && exit 2

touch $FLAG

source ~/.profile

source $LABRADOR_CONFIG

if test -z "$*"; then
	SITES=`ls $LABRADOR_SITES`
else
	SITES=$*
fi

for SITE in ${#SITES[@]}; 
do
	SITE_ROOT=$LABRADOR_SITES/$SITE
	SITE_CONF=$SITE_ROOT/config/site.conf
	CONF_DIR=$LABRADOR/etc

	log "Begin processing site $SITE"
	
	log "Launch Spider"
	$SPIDER_PATH --site-config=$SITE_CONF \
		--worker-dir=$SITE_ROOT/workers/spider \
		--shared-dir=$SITE_ROOT/workers/shared \
		--config-dir=$CONF_DIR/spider \
		--rule-dir=$SITE_ROOT/rules/spider \
		--log-file=$SITE_ROOT/logs/spider.log

	log "Launch Parser"
	$PARSER_PATH --site-config=$SITE_CONF \
		--source-dir=$SITE_ROOT/workers/spider \
		--worker-dir=$SITE_ROOT/workers/parser \
		--shared-dir=$SITE_ROOT/workers/shared \
		--config-dir=$CONF_DIR/parser \
		--rule-dir=$SITE_ROOT/rules/parser \
		--log-file=$SITE_ROOT/logs/parser.log

	log "Launch Reactor"
	$REACTOR_PATH --site-config=$SITE_CONF \
		--source-dir=$SITE_ROOT/workers/parser \
		--worker-dir=$SITE_ROOT/workers/reactor \
		--shared-dir=$SITE_ROOT/workers/shared \
		--config-dir=$CONF_DIR/reactor \
		--rule-dir=$SITE_ROOT/rules/reactor \
		--log-file=$SITE_ROOT/logs/reactor.log

	log "Launch Assembler"
	$ASSEMBLER_PATH --site-config=$SITE_CONF \
		--source-dir=$SITE_ROOT/workers/reactor \
		--worker-dir=$SITE_ROOT/workers/assembler \
		--shared-dir=$SITE_ROOT/workers/shared \
		--webroot-dir=$SITE_ROOT/webroot \
		--config-dir=$CONF_DIR/assembler \
		--rule-dir=$SITE_ROOT/rules/assembler \
		--log-file=$SITE_ROOT/logs/assembler.log

	log "End processing site $SITE"
done

rm $FLAG

# Known bug: if a site is deleted while running scheduler, error may occurs.
