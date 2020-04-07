#!/bin/sh

# Launch tcpdump in the background. It awaits the kill switch.
# MJB 07/04/2020

iface="$1"
pcapFile="$2"

if [ ! -n "$iface" ] || [ ! -n "$pcapFile" ]; then
    echo "$0: Arguments missing. Aborting."
    exit 1
fi

echo "started: $(date) iface: $iface pcapFile: $pcapFile" > tcpderror.log
nohup sudo tcpdump -i "$iface" -N -n 'tcp port 1935' -w "$pcapFile" 2>> tcpderror.log 1>/dev/null &
