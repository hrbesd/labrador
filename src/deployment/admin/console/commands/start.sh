# Installing scheduler into cron

#write out current crontab
crontab -l > /tmp/mycron

echo "00 00 * * * $SCHEDULER_PATH" >> /tmp/mycron

#install new cron file
crontab /tmp/mycron
rm /tmp/mycron

log "Service started."
