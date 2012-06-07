text_dir='text'
audio_dir='audio'

while true
do
	queue_head=`ls -tr $text_dir | head -n 1`
	queue_head="$text_dir/$queue_head"
	
	if test -f "$queue_head"; then
		output="$audio_dir/"`basename $queue_head '.txt'`'.m4a'
		say -v 'Ting-ting' -f $queue_head -o $output
		rm $queue_head
	else
		sleep 1
		echo "Waiting for text."
	fi
done