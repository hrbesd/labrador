fail_unless_in_repo
# Backup site config
cp $SITE_ROOT/config/site.conf /tmp/
rm -rf $SITE_ROOT
cp -r $LABRADOR_TEMPLETS $SITE_ROOT
cp /tmp/site.conf $SITE_ROOT/config/

log "Site reset."
