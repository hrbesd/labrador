test -f "$1" || exit 1

# Word Count
printf "Word Count:\t"
wc -m $1

# Speed Test
OUTPUT='v.aiff'
time say -v Ting-Ting -o "$OUTPUT" -f $1 
echo

# Audio Size
printf "Audio File:\t$OUTPUT\n"
printf "File Size:\t`stat -f %z $OUTPUT` bytes\n"
