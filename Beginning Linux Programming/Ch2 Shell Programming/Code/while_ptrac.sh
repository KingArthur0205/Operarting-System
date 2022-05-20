#!/bin/sh

echo "Enter password."
read input

while [ $input != "secret" ]
do
	echo "Wrong password. Try again"
	read input
done

exit 0