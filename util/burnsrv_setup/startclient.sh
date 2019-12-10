#!/bin/bash

# APPROXIMATE MEMORIES CLIENT SCRIPT
# Silent operation; pipes to dev/null
# Author: MJB Authored: 10-12-2019

if [ ! -s "stream.config" ]; then
   echo "Please ensure that stream.config is in the same dir as $0." 
   exit 1
fi

. stream.config

ffmpeg -y -i $defaultServer -acodec copy -vcodec copy -f flv /dev/null
