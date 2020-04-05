#!/bin/bash

# Test Runner master script
# by MJB, 05/04/2020

if [ ! -s "stream.config" ]; then
    echo "Critical failure: stream.config file doesn't exist or is empty. Exiting."
    exit 1
fi

. stream.config

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
echo "Running NTP sync operation for all hosts..."
for server in "${streamServers[@]}"; do
    ssh "${userName}@${server}" sudo ntpdate -q "$ntpHost"
    sleep 1
    ssh "${userName}@${server}" sudo systemctl restart ntp
    sleep 1
done
echo "Time sync complete."

# get start time
startTime="$( date +'%M %S %N' )"

# then run tcpdump locally and remotely.
echo "Launching tcpdump and performing stream on each specified server."
for server in "${streamServers[@]}"; do
    ssh "${userName}@${server}" "sudo tcpdump -i eth0 -N -n tcp port 1935 -w qub-testrun.pcap"
    echo "Beginning stream in 4..."
    sleep 4
    ./startclient.sh -v -n 1 -s "rtmp://${server}:${rtmpPort}/${rtmpPath}/${streamFiles[0]}.${streamFormat}"
done
echo "Launches complete."

# Run stream for one client.

# Retrieve tcpdump captures, remove old capture, launch slogger for analysis
