#!/bin/bash

# Greenwich: script to verify that two servers times are synced.
# Author: MJB Authored: 05/04/2020
# Requires Chrony and Cron installed on all hosts.

if [ ! -s "stream.config" ]; then
    echo "Error, need user profile and servers from stream.config."
    exit 1
fi

if [ "$1" = "-h" ]; then
    echo "Greenwich server sync tool."
    echo "Use -s just to sync servers. Run with no args to sync and compare times."
    exit 0
fi

. stream.config

if [ "$cleanCron" = "true" ]; then
   echo "Warning: cleanCron is true. This will wipe the cron jobs for $userName on each host!" 
fi

# Perform sync with the same ntp server.
if [ "$skipSync" != "true" ]; then
    echo "Running a triple NTP sync operation for all hosts..."
    for server in "${streamServers[@]}"; do
        # TODO: $ntpHost didn't play well with ssh, so we hard-coded it.
        ssh "${userName}@${server}" "sudo chronyd -q 'server 0.uk.pool.ntp.org iburst'"
        sleep 1
        ssh "${userName}@${server}" "sudo chronyd -q 'server 0.uk.pool.ntp.org iburst'"
        sleep 1
        ssh "${userName}@${server}" "sudo chronyd -q 'server 0.uk.pool.ntp.org iburst'"
        sleep 1
    done
    if [ "$doLocal" = "true" ]; then
        sudo chronyd -q "server $ntpHost iburst"
        sleep 1
        sudo chronyd -q "server $ntpHost iburst"
        sleep 1
        sudo chronyd -q "server $ntpHost iburst"
        sleep 1
    fi
    echo "Time sync complete."
fi

# We want sync only, so exit now.
if [ "$1" = "-s" ]; then
    exit 0
fi

# Set cron job to dump time in 1 minute.

echo "Setting cron job to dump time in 1m for all hosts..."
for server in "${streamServers[@]}"; do
    scp -q "./gpolltime.sh" "${userName}@${server}:/home/$userName/"
    ssh "${userName}@${server}" "echo -e '* * * * * /home/$userName/gpolltime.sh' \"\n\" | crontab"
done

if [ "${doLocal}" = "true" ]; then
    echo -e '* * * * * /home/mjb/gpolltime.sh' "\n" | crontab
fi

echo "Cron task setting complete."

# Wait 80 seconds. Thereafter, grab the times and compare.
echo "Waiting $delay seconds."
sleep $delay

if [ ! -d "$timedir" ]; then
    mkdir "$timedir"
fi

echo "Fetching recorded times from servers."
for server in "${streamServers[@]}"; do
    scp "${userName}@${server}:/tmp/greenwich" "./$timedir/$server"
    ssh "${userName}@${server}" "rm /tmp/greenwich"
done

if [ "$doLocal" = "true" ]; then
    mv "/tmp/greenwich" "./$timedir/localhost"
fi

# clean cron tables if specified
if [ "$cleanCron" = "true" ]; then
    echo "Clearing cron tables."
    for server in "${streamServers[@]}"; do
        ssh "${userName}@${server}" "crontab -r"
    done
fi

# Print time and server name.
for thisFile in $( ls ./$timedir/ ); do
    echo "$thisFile reported $( cat ./$timedir/$thisFile )"
done


