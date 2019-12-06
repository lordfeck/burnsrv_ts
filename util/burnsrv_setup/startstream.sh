#!/bin/bash

# Start Stream script for Approximate Memories
# Author: MJB Authored: 06-12-19

. stream.config

readonly banner="START STREAM SCRIPT\nUsage:\n-i <stream input>
-o Stream server output\n-h show help
Running with no input will use the settings in stream.config."

# Handle arguments
while getopts ":i:h" opt; do
    case $opt in
        i ) stream="$OPTARG" ;;
        o ) server="$OPTARG" ;;
        h ) echo -e "$banner"; exit 0 ;;
        \? ) echo -e "Invalid Argument.\n$banner"; exit 1 ;;
    esac
done

# If no stream is provided use default.
if [ -z $stream ]; then
    echo "Beginning run of configured stream $defaultStream."
    stream="$defaultStream"
fi

if [ -z $server ]; then
    echo "Using configured server $defaultServer."
    server="$defaultServer"
fi

# Begin stream
ffmpeg -i $stream -f flv $server 
