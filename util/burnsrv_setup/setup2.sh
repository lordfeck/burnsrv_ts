#!/bin/bash

# APRROXIMATE MEMORIES SETUP SCRIPT
# V1.0 (short) 04-12-2019
# Author: MJB

readonly vidDir="/var/bbc1/"
readonly htmlDir="/var/www/"
readonly nginxConfigDir="/etc/nginx/"
readonly banner="setup2.sh: Use -w to copy just WWW\nUse -c to copy just config.\nRun with no flags to perform a full install."

function create_dirs
{
    
    echo "Creating $vidDir dir for stream and copying video."
    mkdir -p $vidDir
    cp -nfv bbc1/* $vidDir
}

function copy_html
{
    echo "Copying HTML into $htmlDir."
    cp -rfv www/* $htmlDir  
}

function copy_config
{
    echo "Copying config to $nginxConfigDir."
    cp -fv config/nginx.conf $nginxConfigDir
    cp -fv config/default $nginxConfigDir/sites-available 
}

function restart_nginx
{
    echo "Restarting Nginx..."
    systemctl restart nginx
}

echo "Beginning Burnsrv Setup..."

opsys=$(lsb_release -is)

echo "Detected OS: ${opsys}"

if [ $(id -u) -ne "0" ]; then
    echo "Please run as root or sudo."
    exit 1
fi

# We might want to just copy html or config
if [ "$1" = "-w" ]; then
    copy_html
    exit 0
elif [ "$1" = "-c" ]; then
    copy_config
    restart_nginx
    exit 0
elif [ "$1" = "-h" ]; then
    # display help
    echo -e $banner
    exit 0
fi

# Begin main body of script

copy_config
create_dirs
copy_html
restart_nginx
