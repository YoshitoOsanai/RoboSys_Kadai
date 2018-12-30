#!/bin/bash

make 
rmmod myled
insmod myled.ko
sudo chmod 666 /dev/myled0
