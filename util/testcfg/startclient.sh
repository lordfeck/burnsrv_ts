#!/bin/bash

# APPROXIMATE MEMORIES LOCAL CLIENT SCRIPT
# Silencer attachment; pipes to /dev/null
# Author: MJB Authored: 10-12-2019

readonly maxCountPrint="10"
readonly banner="Start Client Stream. Usage:\n\
    -h show help\n\
    -l stream using live stream\n\
    -v stream using VOD\n\
    -s <stream path> supply stream url manually\n\
    -n <client count> for VOD\n\
    -t <maxtime> Stream until then. Passed straight to FFMPEG -t.\n\
    Requires stream.config to be configured correctly.\n"

function liveStream {
    ffmpeg -y -i $stream -acodec copy -vcodec copy -f flv /dev/null
}

function vodStream {
    ffmpeg -loglevel error -y -i $stream -t $maxTime -acodec copy -vcodec copy -f flv /dev/null
}

function spawnStreams {
    if [ "$clientCount" -eq "1" ]; then
        vodStream
        return
    fi

    while [ "0" -lt "$clientCount" ]; do
        vodStream &
        ((clientCount--))
    done

    echo "Client spawn complete."
    wait
}

if [ ! -s "stream.config" ]; then
   echo "Please ensure that stream.config is in the same dir as $0." 
   exit 1
fi

. stream.config

# Set to defaults first then let getopts overwrite
streamMode="$defaultMode"
clientCount="$defaultClientCount"

while getopts ":hlvn:s:t:" opt; do
    case $opt in
        l ) streamMode="live" ;;
        v ) streamMode="vod" ;;
        n ) clientCount="$OPTARG" ;;
        s ) suppliedStream="$OPTARG" ;;
        h ) echo -e "$banner"; exit 0 ;;
        t ) maxTime="$OPTARG" ;;
        \? ) echo -e "Invalid Argument.\n$banner"; exit 1 ;;
    esac
done

if [ ! -n "$suppliedStream" ]; then
    echo "Using default stream from stream.config."
fi

if [ "$streamMode" = "live" ]; then
    # Assign the supplied stream argument; if unset use default
    stream=${suppliedStream:-"$defaultServer"}
    echo "Beginning live stream of $stream."
    echo "Client count is discarded."
    liveStream
elif [ "$streamMode" = "vod" ]; then
    # assign the supplied stream argumet; if unset use default
    stream=${suppliedStream:-"$defaultVodStream"}
    echo "VOD mode selected for $stream. Spawning $clientCount clients."
    spawnStreams 
else
    echo "Invalid stream configuration."
    exit 1
fi
