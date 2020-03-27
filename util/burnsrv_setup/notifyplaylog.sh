#!/bin/bash

# if in doubt, script the bit out

playlog="/local/mbrown49/burnsrv/playlog"

if [ "$1" = "-e" ]; then
    echo "$(date) PLAY END" >> $playlog
    exit 0
fi

# to clear
if [ "$1" = "-c" ]; then
    echo "" > $playlog
fi

# default - log play
echo "$(date) PLAY START" >> $playlog

