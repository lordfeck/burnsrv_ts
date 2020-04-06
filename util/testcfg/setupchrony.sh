#!/bin/bash

# Setup script that copies and installs chrony.
# Use to quickly setup a stream server before timesync.
# Author: MJB Authored: 06/04/2020

echo "Time Sync Interacvtive Setup Script."

if [ $(id -u) -ne "0" ]; then
    echo "Please run as root or sudo."
    exit 1
fi

mkdir -p "/etc/chrony/"
cp -v "./conf/chrony.conf" "/etc/chrony/chrony.conf"

apt install chrony
sleep 2
systemctl start chronyd
systemctl enable chronyd

sleep 2
chronyd -q 'server 0.uk.pool.ntp.org iburst'
