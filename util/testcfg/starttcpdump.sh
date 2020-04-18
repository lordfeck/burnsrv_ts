#!/bin/sh

# Launch tcpdump in the background. It awaits the kill switch.
# MJB 07/04/2020

iface="$1"
pcapFile="$2"
tcpderr="${3:-tcpderror.log}"

if [ ! -n "$iface" ] || [ ! -n "$pcapFile" ]; then
    echo "$0: Arguments missing. Aborting."
    exit 1
fi

echo "started: $(date) iface: $iface pcapFile: $pcapFile" > "$tcpderr"
nohup sudo tcpdump -i "$iface" -N -n 'tcp port 1935' -B 10000 -w "$pcapFile" 2>> "$tcpderr" 1>/dev/null &

if [ "$?" -ne 0 ]; then
    echo "Problem starting TCPdump." >> "$tcpderr"
    exit 1
fi
