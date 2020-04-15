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
    echo "CRITICAL: Error when $1. Exiting."
    exit 1
fi
}

function checkWarning {
if [ "$?" -ne "0" ]; then
    echo "WARNING: Failure when $1. Please check the configuration!"
fi
}

# BEGIN PREPARATION SECTION
# If Cap dir doesn't exist, make it.
if [ ! -d "${capDir}/prev/" ]; then
    mkdir -p "${capDir}/prev/"
fi

# Output diagnostic info.
echo "Welcome to testrunner."

echo -n "Stream server list: "
for server in "${streamServers[@]}"; do
    echo -n "$server, "
done
echo ""

#echo -n "These are: "
#for desc in "${streamServersDesc[@]}"; do
#    echo -n "$desc, "
#done
#echo ""

# Test for local presence of tcpdump
if ! which tcpdump >/dev/null; then
    echo "Tcpdump is not installed. Cannot continue." 1>&2
    exit 1
fi

# Sync time of all servers.
if [ "$skipTestSync" != "true" ]; then
    ./greenwich.sh -s
fi

# get start time
startTime="$( date +'%M %S %N' )"

# END PREP

# BEGIN MAIN TEST RUN LOOP
# Run tcpdump locally and remotely. Start stream for one client (TODO: expand if necessary)
echo "Launching tcpdump and performing stream on each specified server."

# Backup previous captures
find ${capDir}/* -maxdepth 0 -type f -exec mv -f -v {} ${capDir}/prev/ \;

for server in "${streamServers[@]}"; do
    scp -q "starttcpdump.sh" "${userName}@${server}:/home/$userName/"
    sleep 1
    ssh "${userName}@${server}" "/home/$userName/starttcpdump.sh eth0 $pcapFileName"
    checkError "Beginning remote tcpdump for $server."
    ./starttcpdump.sh "$localIface" "./$capDir/$server.local"
    checkError "Beginning local tcpdump for ${server}"
    echo "Beginning stream in 4..."
    sleep 4
    ./startclient.sh -v -n 1 -s "rtmp://${server}:${rtmpPort}/${rtmpPath}/${streamFiles[0]}.${streamFormat}" -t "$streamMaxLength"
    checkError "Beginning ${server}'s stream."
    echo "Stream over, killing remote and local tcpdump."
    sleep 4
    ssh "${userName}@${server}" 'sudo kill -2 `pgrep tcpdump`'
    checkWarning "Killing remote TCPdump for $server"
    sudo kill -2 `pgrep tcpdump` 2>&1 >/dev/null
    checkWarning "Killing local TCPdump for $server"
    # remove any output from local tcpd run (uncomment to debug)
    #rm -vf "tcpderror.log"
done

echo "Correcting ownership inside $capDir recursively."
sudo chown -R $localUser $capDir

# END MAIN

# BEGIN HOUSEKEEPING & ANALYSIS
# Retrieve tcpdump captures & remove old captures 
echo "Retrieving and/or removing=$removeOldCap old captures..."
for server in "${streamServers[@]}"; do
    scp "${userName}@${server}:/home/$userName/$pcapFileName" "./$capDir/$server.remote"
    if [ "$removeOldCap" = "true" ]; then
        ssh "${userName}@${server}" rm "/home/$userName/$pcapFileName"
    else
        echo "Old capture left on $server."
    fi
done

# launch slogger for analysis
echo "Launching slogger... NOT YET"

# END HOUSEKEEPING
