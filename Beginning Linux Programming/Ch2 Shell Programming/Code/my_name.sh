#!/bin/sh

yes_or_no() {
	echo "Is this your name?"
	while true
	do
		echo "Please input yes/no: "
		read input
		case "$input" in
			y | yes ) return 0;;
			n | no ) return 1;;
			* ) echo "Only yes or no is accepted. Try again."
		esac
	done
}

IFS="@"
echo "The parameters are $*"

echo "Is your name $1?"
if yes_or_no "$1"
then
	echo "Hi, $1"
else
	echo "Sorry, never mind."
fi

exit 0