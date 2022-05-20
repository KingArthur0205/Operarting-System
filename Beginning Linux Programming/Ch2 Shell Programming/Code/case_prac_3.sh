#!/bin/sh

echo "Is it morning or afternoon?"
read input

case $input in
	[yY] | [yY][eE][sS]) echo "Good morning";;
	[nN]*) echo "Good afternoon";;
	*) 
		echo "Wrong input"
		exit 1
		;;
esac

exit 0