#!/bin/sh

#script to copy project files into production directories

LIST="proj1 proj2 proj3"

for proj in $LIST
do
	if [ -d $proj/bin ]; then
		cp $proj/bin/* /opt/verascape/bin 2>/dev/null
		echo "copied $proj/bin/* to /opt/verascape/bin"
	fi

	if [ -d $proj/lib ]; then
		cp $proj/lib/* /opt/verascape/lib 2>/dev/null
		echo "copied $proj/lib/* to /opt/verascape/bin"
	fi
done

exit 0;
