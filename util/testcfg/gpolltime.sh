#!/bin/bash

# MJB's poll time script. For use inside cron and testruns.
# Used with greenwich.sh
# Help: https://stackoverflow.com/questions/16548528/command-to-get-time-in-milliseconds

# time in ns:
if [ "$1" = "-n" ]; then
    date +"%T.%6N" > /tmp/greenwich
    exit
fi

# time in ms (default):
date +"%T.%3N" > /tmp/greenwich
