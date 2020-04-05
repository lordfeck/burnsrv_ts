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
echo "Stream server list:"
for server in "${streamServers[@]}"; do
    echo "$server"
done
echo "These are:"
for desc in "${streamServersDesc[@]}"; do
    echo "$desc"
done

# Test for local presence of tcpdump
if ! which tcpdump >/dev/null; then
    echo "Tcpdump is not installed. Cannot continue." 1>&2
    exit 1
fi

# Sync time of all servers.

# then run tcpdump locally and remotely.

# Run stream for one client.

