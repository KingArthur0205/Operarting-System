#!/bin/sh

echo -n "Is it morning or afternoon?"
read timeOfDay

if [ "$timeOfDay" = "yes" ]
then
	echo "Good morning"
elif [ "$timeOfDay" = "no" ]
then
	echo "Good afternoon"
else
	echo "Sorry, $timeOfDay is not recognized"
	exit 1
fi

exit 0