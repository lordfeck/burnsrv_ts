#!/bin/bash

# Test Runner master script
# by MJB, 05/04/2020

if [ ! -s "stream.config" ]; then
    echo "Critical failure: stream.config file doesn't exist or is empty. Exiting."
    exit 1
fi

. stream.config
declare -a streamServers shortDescs ifNames
let svrIdx=0

# DEFINE FUNCTIONS

function setTestFlag {
    if [ "$1" = "clear" ]; then
        rm -f /tmp/.testrunning
    else
        touch /tmp/.testrunning
    fi
}

# how to read in csv to bash, src: https://stackoverflow.com/a/4286841/11937530
function readInServers {
    if [ ! -s "$1" ]; then
        echo "Critical failure: $1 server list doesn't exist or is empty. Exiting."
        exit 1
    fi

    let i=0
    while IFS=, read -r hostname shortdesc longdesc ifname
    do
        streamServers[$svrIdx]="$hostname"
        shortDescs[$svrIdx]="$shortdesc"
        ifNames[$svrIdx]="$ifname"
        ((svrIdx++))
    done < "$1"
}

# simple error handling
function checkError {
    if [ "$?" -ne "0" ]; then
        echo "CRITICAL: Error when $1. Exiting."
        setTestFlag "clear"
        exit 1
    fi
}

function checkWarning {
    if [ "$?" -ne "0" ]; then
        echo "WARNING: Failure when $1. Please check the configuration!"
    fi
}

# functions for main loop

function doPing {
    ping -c 3 "$server" | grep avg | cut -d '/' -f 5
}

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

# This will be called once for each configuration by the master loop down below.
# Uses variables declared outside the function body but within its scope.
function doStream {
    server="${streamServers[i]}"
    shortDesc="${shortDescs[i]}"
    ifname="${ifNames[i]}"

    backupOldCaptures

    local myPing="$(doPing)"
    echo "Average ping for $shortDesc is: $myPing."

    scp -q "starttcpdump.sh" "${userName}@${server}:/home/$userName/" 
    sleep 1
    ssh "${userName}@${server}" "/home/$userName/starttcpdump.sh $ifname $pcapFileName $tcpderr"
    checkError "Beginning remote tcpdump for $server."
    ./starttcpdump.sh "$localIface" "./$capDir/$shortDesc.local" "$tcpderr"
    checkError "Beginning local tcpdump for ${server}"
    echo "Beginning stream $currentStreamId out of $totalStreams for $server length $length in 4..."
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
    # update status message for web UI
    echo "$currentStreamId/$totalStreams: Params: $shortDesc-$vid-$res-$quant-$length. Ran for ${ms}ms." > "$lastMsg"

    getRemoteCapture

    # local capfiles have invalid perms (tcpdump user owns it), correct it now
    echo "Correcting ownership inside $capDir recursively."
    sudo chown -R $localUser $capDir

    # get local packet count
    localPackets="$( grep 'packets captured' "$tcpderr" | cut -d ' ' -f1 )"
    checkError "packet count"

    # csv format: vidfile, shortdesc, clientcount, vidlength, quant, res, streamtime, packets, avgping
    echo "$vid,$shortDesc,$testClients,$length,$quant,$res,$runtime,$localPackets,$myPing" >> "$logFilePath"
    ((currentStreamId++))
}

# run this to kill a test in progress
function resetTestEnv {
    readInServers "$serverList"

    echo "Running kill operation on remote server TCPdumps. Errors are expected."

    for server in "${streamServers[@]}"; do
        ssh "${userName}@${server}" 'sudo kill -2 `pgrep tcpdump`' 
        checkWarning "Killing remote TCPdump for $server"
    done

    echo "Killing local tcpdump and ffmpeg processes"
    sudo kill -2 `pgrep tcpdump` 2>&1 >/dev/null
    checkWarning "Killing local TCPdump"

    sudo kill -2 `pgrep ffmpeg` 2>&1 >/dev/null
    checkWarning "Killing local ffmpeg"

    setTestFlag "clear"
    echo "$(date): Controlsrv awaiting command." > $lastMsg
    
}

# if we call script with -r, then reset test environment and exit
if [ "$1" = "-r" ]; then
    resetTestEnv
    exit
fi

# BEGIN PREPARATION SECTION

setTestFlag

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

# BEGIN MAIN TEST RUN BODY

# Set date to identify the test run.
startDate="$( date '+%F-%H%M%S' )"
logFilePath="$logDir/${logBaseName}-${startDate}.csv"
totalStreams="$((${#streamFiles[@]}*${#resolutions[@]}*${#quants[@]}*${#lengths[@]}*${#streamServers[@]}))"
currentStreamId=0;

# First create the blank logfile
touch "$logFilePath"
checkError "accessing the logfile at $logDir/$logFilePath"
echo "Test run on $startDate begins." > "$lastMsg"

echo "Launching tcpdump and performing stream on each specified server."
echo "We have $totalStreams total streams to run."

# BEGIN MASTER LOOP
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
# END MASTER LOOP

# END MAIN BODY

# BEGIN ANALYSIS

# launch slogger for analysis
echo "Launching slogger to generate charts... (not yet implemented)"

# END ANALYSIS
echo "Test run for $startDate complete." | tee "$lastMsg"
setTestFlag "clear"

