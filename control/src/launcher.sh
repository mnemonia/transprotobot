#!/bin/sh
# launcher.sh
# navigate to home directory, then to this directory, then execute python script, then back home

cd /
cd home/pi/Documents/master/transprotobot/control/src
sudo python3 transprotobot.py
cd /