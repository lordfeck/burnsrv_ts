#!/bin/bash

# APRROXIMATE MEMORIES SETUP SCRIPT
# V1.0 04-12-2019
# Author: MJB

function check_ports
{
    local netStOut="$( netstat -nl )"
    echo $netStOut | grep -Eq '(0.0.0.0:)((80)|(1935))\b' --color
}

opsys=$(lsb_release -is)

echo "Beginning Burnsrv Setup..."
echo "Detected OS: ${opsys}"

# Check env

if [ $(id -u) -ne "0" ]; then
    echo "Please run as root or sudo."
    exit 1
fi

if check_ports; then
    echo "Services already found running on either ports 80 or 1935. These are required for nginx and the streamer."
else
    echo "Ports 80 and 1935 are available. Continuing..."
fi
