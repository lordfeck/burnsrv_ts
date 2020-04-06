#!/bin/bash

# Poll time script. For use inside cron.
# Used with greenwich.sh
# Help: https://stackoverflow.com/questions/16548528/command-to-get-time-in-milliseconds

#date "+%M %S %N" > /tmp/greenwich 
#date "+%s%N" > /tmp/greenwich

# time in ms:
date +"%T.%3N" > /tmp/greenwich

