#!/bin/bash

# Test Runner master script
# by MJB, 05/04/2020

if [ ! -s "stream.config" ]; then
    echo "Critical failure: stream.config file doesn't exist or is empty. Exiting."
    exit 1
fi

. stream.config
declare -a streamServers shortDescs
let svrIdx=0

# DEFINE FUNCTIONS

# how to read in csv to bash, src: https://stackoverflow.com/a/4286841/11937530
function readInServers {
    if [ ! -s "$1" ]; then
        echo "Critical failure: $1 server list doesn't exist or is empty. Exiting."
        exit 1
    fi

    let i=0
    while IFS=, read -r hostname shortdesc longdesc
    do
        streamServers[$svrIdx]="$hostname"
        shortDescs[$svrIdx]="$shortdesc"
        ((svrIdx++))
    done < "$1"
}

# simple error handling
function checkError {
    if [ "$?" -ne "0" ]; then
        echo "CRITICAL: Error when $1. Exiting."
        exit 1
    fi
}

function checkWarning {
    if [ "$?" -ne "0" ]; then
        echo "WARNING: Failure when $1. Please check the configuration!"
    fi
}

# functions for main loop

# Grab remote capture (only call inside doStream)
function getRemoteCapture {
    echo "Retrieving ${removeOldCap:+and removing} capture from $shortDesc..."
    scp -q "${userName}@${server}:/home/$userName/$pcapFileName" "./$capDir/$shortDesc.remote"
    checkError "retrieving capture from $server"
    if [ "$removeOldCap" = "true" ]; then
        ssh "${userName}@${server}" rm "/home/$userName/$pcapFileName"
    else
        echo "Old capture left on $server."
    fi
}

# We may want to keep the last run's captures for debugging. If so, call this fn.
function backupOldCaptures {
    2>&1 find ${capDir}/* -maxdepth 0 -type f -exec mv -f -v {} ${capDir}/prev/ \; >/dev/null
    checkWarning "backing up old captures"
}

# This will be called once for each configuration. Uses variables declared
# outside the function body but within its scope.
function doStream {
    server="${streamServers[i]}"
    shortDesc="${shortDescs[i]}"

    backupOldCaptures

    scp -q "starttcpdump.sh" "${userName}@${server}:/home/$userName/" 
    sleep 1
    ssh "${userName}@${server}" "/home/$userName/starttcpdump.sh eth0 $pcapFileName $tcpderr"
    checkError "Beginning remote tcpdump for $server."
    ./starttcpdump.sh "$localIface" "./$capDir/$shortDesc.local" "$tcpderr"
    checkError "Beginning local tcpdump for ${server}"
    echo "Beginning stream for $server length $streamMaxLength in 4..."
    sleep 4

    # %s - seconds since unix epoch, %N is nanoseconds
    before="$( date '+%s%N' )"
    ./startclient.sh -v -n "$testClients" -s "rtmp://${server}:${rtmpPort}/${rtmpPath}/$vid-$quant-$res.$streamContainer" -t "$length"
    after="$( date '+%s%N' )"
    echo "Stream over, killing remote and local tcpdump."
    sleep 4

    ssh "${userName}@${server}" 'sudo kill -2 `pgrep tcpdump`'
    checkWarning "Killing remote TCPdump for $server"
    sudo kill -2 `pgrep tcpdump` 2>&1 >/dev/null
    checkWarning "Killing local TCPdump for $server"

    runtime="$((after-before))"
    ms="$((runtime/1000000))"
    echo "Stream ran for $ms ms"

    getRemoteCapture

    # local capfiles have invalid perms (tcpdump user owns it), correct it now
    echo "Correcting ownership inside $capDir recursively."
    sudo chown -R $localUser $capDir

    # get local packet count
    localPackets="$( grep 'packets captured' "$tcpderr" | cut -d ' ' -f1 )"
    checkError "packet count"

    # csv format: vidfile, shortdesc, clientcount, vidlength, quant, res, streamtime, packets
    echo "$vid,$shortDesc,$testClients,$length,$quant,$res,$runtime,$localPackets" >> "$logFilePath"
}

# BEGIN PREPARATION SECTION
readInServers "$serverList"

# If Cap dir doesn't exist, make it.
if [ ! -d "${capDir}/prev/" ]; then
    mkdir -p "${capDir}/prev/"
fi

# If log dir doesn't exist, make it.
if [ ! -d "${logDir}/" ]; then
    mkdir "${logDir}/"
fi

# Output diagnostic info.
echo "Welcome to testrunner."

echo -n "Stream server list: "
for server in "${streamServers[@]}"; do
    echo -n "$server, "
done
echo ""

# Test for local presence of tcpdump
if ! which tcpdump >/dev/null; then
    echo "Tcpdump is not installed. Cannot continue." 1>&2
    exit 1
fi

# NTP sync time of all servers.
if [ "$skipTestSync" != "true" ]; then
    ./greenwich.sh -s
fi

# END PREP

# BEGIN MAIN TEST RUN LOOP

# Set date to identify the test run.
startDate="$( date '+%F-%H%M%S' )"
logFilePath="$logDir/${logBaseName}-${startDate}.csv"
totalStreams="$((${#streamFiles[@]}*${#resolutions[@]}*${#quants[@]}*${#lengths[@]}*${#streamServers[@]}))"

# First create the blank logfile
touch "$logFilePath"
checkError "accessing the logfile at $logDir/$logFilePath"

echo "Launching tcpdump and performing stream on each specified server."
echo "We have $totalStreams total streams to run."

# Yes, there are many loops. But this allows for limitless expansion.
for vid in "${streamFiles[@]}"; do
    for res in "${resolutions[@]}"; do
        for quant in "${quants[@]}"; do
            for length in "${lengths[@]}"; do
                # BEGIN SERVER LOOP - i is used inside doStream.
                let i=0
                while [ "$i" -lt "$svrIdx" ]; do
                    doStream
                    ((i++))
                done
                # END SERVER LOOP
            done
        done
    done
done

# END MAIN

# BEGIN ANALYSIS

# launch slogger for analysis
echo "Launching slogger... NOT YET"

# END ANALYSIS
