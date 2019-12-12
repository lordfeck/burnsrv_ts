#!/bin/bash

# APPROXIMATE MEMORIES CLIENT SCRIPT
# Silent operation; pipes to dev/null
# Author: MJB Authored: 10-12-2019
readonly banner="Start Client Stream. Usage:\n\
    -h show help\n\
    -l stream using live stream\n\
    -v stream using VOD\n\
    -n <client count> for VOD\n\
    Requires stream.config to be configured correctly.\n"

function liveStream {
    ffmpeg -y -i $stream -acodec copy -vcodec copy -f flv /dev/null
}

function vodStream {
    ffmpeg -loglevel error -y -i $stream -acodec copy -vcodec copy -f flv /dev/null
}

function spawnStreams {
    if [ "$clientCount" -ge "50" ]; then
        echo "Over 50 clients spawned. Skipping some individual messages."
    fi

    while [ "0" -lt "$clientCount" ]; do
        vodStream &
        ((clientCount--))

        if [ "$clientCount" -le "50" ]; then
            echo "SPAWNED $clientCount"
        fi
    done

    echo "Client spawn complete. Awaiting user interrupt."
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

while getopts ":hlvn:" opt; do
    case $opt in
        l ) streamMode="live" ;;
        v ) streamMode="vod" ;;
        n ) clientCount="$OPTARG" ;;
        h ) echo -e "$banner"; exit 0 ;;
        \? ) echo -e "Invalid Argument.\n$banner"; exit 1 ;;
    esac
done

if [ "$streamMode" = "live" ]; then
    stream="$defaultServer"
    echo "Beginning live stream of $stream."
    echo "Client count is discarded."
    liveStream
elif [ "$streamMode" = "vod" ]; then
    stream="$defaultVodStream"
    echo "VOD mode selected for $stream."
    echo "Spawning $clientCount clients."
    # This uses Bash job control; there may be a better way!
    spawnStreams 
else
    echo "Invalid stream configuration."
    exit 1
fi
