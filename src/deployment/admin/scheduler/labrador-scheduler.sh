source ~/.profile

source $LABRADOR_CONFIG

log()
{
	printf "`date '+%Y-%m-%d %H:%M:%S'`\t$*\n" >>$LABRADOR_LOG/scheduler.log
}

for SITE in `ls $LABRADOR_SITES`
do
	SITE_ROOT=$LABRADOR_SITES/$SITE
	SITE_CONF=$SITE_ROOT/config/site.conf

	log "Begin processing site $SITE"
	
	log "Launch Spider"
	$SPIDER_PATH --site-config=$SITE_CONF \
		--worker-dir=$SITE_ROOT/workers/spider \
		--shared-dir=$SITE_ROOT/workers/shared \
		--rule-dir=$SITE_ROOT/rules/spider \
		--log-file=$SITE_ROOT/logs/spider.log

	log "Launch Parser"
	$PARSER_PATH --site-config=$SITE_CONF \
		--worker-dir=$SITE_ROOT/workers/parser \
		--shared-dir=$SITE_ROOT/workers/shared \
		--rule-dir=$SITE_ROOT/rules/parser \
		--log-file=$SITE_ROOT/logs/parser.log

	log "Launch Reactor"
	$REACTOR_PATH --site-config=$SITE_CONF \
		--worker-dir=$SITE_ROOT/workers/reactor \
		--shared-dir=$SITE_ROOT/workers/shared \
		--rule-dir=$SITE_ROOT/rules/reactor \
		--log-file=$SITE_ROOT/logs/reactor.log

	log "Launch Assembler"
	$ASSEMBLE_PATH --site-config=$SITE_CONF \
		--worker-dir=$SITE_ROOT/workers/assembler \
		--shared-dir=$SITE_ROOT/workers/shared \
		--rule-dir=$SITE_ROOT/rules/assembler \
		--log-file=$SITE_ROOT/logs/assembler.log

	log "End processing site $SITE"
done

# Known bug: if a site is deleted while running scheduler, error may occurs.
