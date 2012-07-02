butts=(generator spider parser reactor assembler)

for butt in "${butts[@]}"; do
	echo "#!/bin/bash" >$butt
	echo "echo [`date`]  I am *$butt* ! You sent me: "'$*' >>$butt
	echo "sleep 1" >>$butt
	chmod +x $butt
done
