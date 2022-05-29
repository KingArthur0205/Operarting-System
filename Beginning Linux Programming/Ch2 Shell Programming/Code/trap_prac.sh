#!/bin/sh

# INT signal is sent when pressing CTRL+C
trap "rm -rf ./tmp_file" INT
touch "./tmp_file"
while [ -f "./tmp_file" ]; do
	echo File exists
	sleep 1
done

# No command is passed. Nothing happens when pressing CTRL+C
trap INT
touch "./tmp_file"
while [ -f "./tmp_file" ]; do
	echo File exists
	sleep 1
done
# ./tmp_file won't be deleted

exit 0