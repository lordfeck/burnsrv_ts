#!/bin/bash

# Start Stream script for Approximate Memories
# Author: MJB Authored: 06-12-19

. stream.config

readonly banner="START STREAM SCRIPT\nUsage:\n-i <stream input file>
-o <Stream server output URL>\n-e <encoding>\n-h show help
Running with no input will use the settings in stream.config."

# Handle arguments
while getopts ":i:ho:e:" opt; do
    case $opt in
        i ) stream="$OPTARG" ;;
        o ) server="$OPTARG" ;;
        e ) encoding="$OPTARG" ;;
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

if [ -z $encoding ]; then
    echo "Using configured server $defaultEncoding."
    encoding="$defaultEncoding"
fi

# Begin stream
ffmpeg -i $stream -f $encoding $server 
