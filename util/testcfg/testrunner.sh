#!/bin/bash

# Test Runner master script
# by MJB, 05/04/2020

if [ ! -s "stream.config" ]; then
    echo "Critical failure: stream.config file doesn't exist or is empty. Exiting."
    exit 1
fi

. stream.config


function checkError {
if [ "$?" -ne "0" ]; then
    echo "Critical error when $1. Exiting."
    exit 1
fi
}

# BEGIN PREPARATION SECTION
# If Cap dir doesn't exist, make it.
if [ ! -d "$capDir" ]; then
    mkdir -p "$capDir"
fi

if [ "$clearCapDir" = "true" ]; then
    rm -f $capDir/*
fi

# Output diagnostic info.
echo "Welcome to testrunner. My tasks are as follows:"

echo -n "Stream server list: "
for server in "${streamServers[@]}"; do
    echo -n "$server, "
done
echo ""

echo -n "These are: "
for desc in "${streamServersDesc[@]}"; do
    echo -n "$desc, "
done
echo ""

# Test for local presence of tcpdump
if ! which tcpdump >/dev/null; then
    echo "Tcpdump is not installed. Cannot continue." 1>&2
    exit 1
fi

# Sync time of all servers.
if [ "$skipSync" != "true" ]; then
    ./greenwich.sh -s
fi

# get start time
startTime="$( date +'%M %S %N' )"

# END PREP

# BEGIN MAIN TEST RUN LOOP
# Run tcpdump locally and remotely. Start stream for one client (TODO: expand if necessary)
echo "Launching tcpdump and performing stream on each specified server."
for server in "${streamServers[@]}"; do
    ssh "${userName}@${server}" "sudo tcpdump -i eth0 -N -n 'tcp port 1935' -w $remotePcapFile &"
    echo "Beginning stream in 4..."
    sleep 4
    ./startclient.sh -v -n 1 -s "rtmp://${server}:${rtmpPort}/${rtmpPath}/${streamFiles[0]}.${streamFormat}" -t "$streamMaxLength"
    echo "Stream over, killing remote tcpdump."
    ssh "${userName}@${server}" 'sudo kill -2 $(pgrep tcpdump)'
done

# END MAIN

# BEGIN HOUSEKEEPING & ANALYSIS
# Retrieve tcpdump captures & remove old captures 
echo "Retriving and/or removing ($removeOldCap) old captures..."
for server in "${streamServers[@]}"; do
    scp "${userName}@${server}:/home/$userName/$remotePcapFile" "./$capDir/$server.remote"
    if [ "$removeOldCap" = "true" ]; then
        ssh "${userName}@${server}" rm "/home/$userName/$remotePcapFile"
    else
        echo "Old capture left on $server."
    fi
done

# launch slogger for analysis
echo "Launching slogger... NOT YET"

# END HOUSEKEEPING
