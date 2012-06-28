# Uninstall scheduler from cron
#write out current crontab
crontab -l > /tmp/mycron

SCRIPT_NAME=`basename $SCHEDULER_PATH`
# sed needs quoting path, so use base name
sed -e '/'$SCRIPT_NAME'/d' -i /tmp/mycron

#install new cron file
crontab /tmp/mycron
rm /tmp/mycron
