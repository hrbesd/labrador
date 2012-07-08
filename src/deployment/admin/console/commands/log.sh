case $1 in
	--console)
		less $LABRADOR_LOG/console.log
		;;
	--scheduler,--daemon)
		less $LABRDOR_LOG/scheduler.log
		;;
	*)
		if site_exists $1; then
			local log_dir=$LABRADOR_SITES/$1/logs
		else
			local log_dir=$LABRADOR_LOG
		fi
		
		for l in `ls -tr $log_dir`
		do
			printf "\n$l:\n\n"
			tail -20 $l
		done
		;;
esac