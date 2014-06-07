#!/bin/sh
# A script to allow usage of the notify-send program to display notifications
# in a particular users X session

user=`whoami`
pids=`pgrep -u $user xfce4-panel`
title=$1
text=$2
icon=$3
timeout=$4

if [ -z "$title" ]; then
 echo You need to give me a title >&2
 exit 1
fi
if [ -z "$text" ]; then
 text=$title
fi
if [ -z "$timeout" ]; then
 timeout=0
fi
 
for pid in $pids; do
 # find DBUS session bus for this session
 DBUS_SESSION_BUS_ADDRESS=`grep -z DBUS_SESSION_BUS_ADDRESS \
 /proc/$pid/environ | sed -e 's/DBUS_SESSION_BUS_ADDRESS=//'`
 # use it
 
 #icon hack:
 if [ -z $icon ]; then
 DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS \
 notify-send -u low -t $timeout "$title" "$text"
 else
 DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS \
 notify-send -u low -t $timeout -i "$icon" "$title" "$text"
 fi
done
