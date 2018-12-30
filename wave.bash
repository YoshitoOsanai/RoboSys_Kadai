#!/bin/bash

while :
do
	echo 1 > /dev/myled0
	sleep 0.5
	echo 2 > /dev/myled0
	sleep 0.5
	echo 3 > /dev/myled0
	sleep 0.5
	echo 4 > /dev/myled0
	sleep 0.5
	echo 5 > /dev/myled0
	sleep 0.5
	echo 4 > /dev/myled0
	sleep 0.5
	echo 3 > /dev/myled0
	sleep 0.5
	echo 2 > /dev/myled0
	sleep 0.5
done
