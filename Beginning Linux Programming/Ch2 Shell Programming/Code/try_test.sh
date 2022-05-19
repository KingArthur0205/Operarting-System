#!/bin/sh

if [ $# -eq 0 ]
then
	exit 0
fi

file=$1

if [ -f $file ]
then
	echo "$file is a file"
fi

if [ -d $file ]
then
	echo "$file is a directory"
else
	echo "$file is not a directory"
fi

exit 0