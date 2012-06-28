source ~/.profile

if test ! -f $LABRADOR_CONFIG; then
	echo "Error: config file not found."
	exit 1
fi

source $LABRADOR_CONFIG

get_siteroot()
{
	while test ! -f '.siteroot'
 	do
		cd ..
		test "`pwd`" == '/' && break
	done
	test `pwd` != '/' && printf `pwd`
}

