locate_site

test -f $SITE_ROOT/SITE_DOWN && printf "\nSite is down.\n"
printf "\nWorkers:\n"
printf "\tDir Count:\t"
find $SITE_ROOT/workers -type d | wc -l 
printf "\tFile Count:\t"
find $SITE_ROOT/workers -type f | wc -l
printf "\tLastModified:\t"
stat -c %y $SITE_ROOT/workers

printf "\nWeb Root:\n"
printf "\tDir Count:\t"
find $SITE_ROOT/webroot -type d | wc -l 
printf "\tFile Count:\t"
find $SITE_ROOT/webroot -type f | wc -l
printf "\tLastModified:\t"
stat -c %y $SITE_ROOT/webroot

printf "\nDisk Usage:\n"
du -h --max-depth=1
