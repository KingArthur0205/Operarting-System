#!/bin/sh

echo "Is it morning or afternoon?"
read input

case $input in
	yes | YES | Yes) echo "Good morning";;
	n* | N*) echo "Good afternoon";;
	*) echo "Wrong input";;
esac

exit 0