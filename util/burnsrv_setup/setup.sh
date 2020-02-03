#!/bin/bash

# APRROXIMATE MEMORIES SETUP SCRIPT
# V1.1 04-12-2019
# Author: MJB

. setup.config

readonly banner="setup.sh: Use -w to copy just WWW\nUse -c to copy just config.\nRun with no flags to perform a full install.\n-p Skip port check."

function check_ports
{
    local netStOut="$( netstat -nl )"
    
    if echo $netStOut | grep -Eq '(0.0.0.0:)((80)|(1935))\b' --color ; then
        echo "Services already found running on either ports 80 or 1935. These are required for nginx and the streamer."
        exit 1
    else
        echo "Ports 80 and 1935 are available. Continuing..."
    fi
}

function check_os
{
    if [ "$opsys" = "Ubuntu" ]; then
        echo "Using APT and DPKG for Ubuntu."
        packager="apt-get -qy install"
        query="dpkg -s"
    elif [ "$opsys" = "CentOS" ]; then
        echo -e "Note: libnginx-mod-rtmp isn't available in YUM repositories.\nPlease install manually."
        packager="yum -qy install"
        query="rpm -q"
    else
        echo "Unsupported OS. Only CentOS and Ubuntu are supported."
        exit 1
    fi
}

function create_dirs
{
    echo "Creating $vidDir dir for stream and copying video."
    mkdir -p $vidDir
    cp -nv bbc1/* $vidDir
    echo "Creating directory for HTML."
    mkdir -p $htmlDir
    echo "Setting ownership for $userName on $rootDir."
    chown -R $userName $rootDir
}

function copy_html
{
    echo "Copying HTML into $htmlDir."
    cp -rfv www/* $htmlDir  
    echo "Setting recursive ownership for $userName on $htmlDir."
    chown -R $userName $htmlDir
}

function copy_config
{
    echo "Copying config to $nginxConfigDir."
    cp -fv config/nginx.conf $nginxConfigDir
    cp -fv config/default $nginxConfigDir/sites-available 
}

function edit_config
{
    echo "Editing config files in $nginxConfigDir with correct WWWroot."
    sed -i "s/##WWWROOT##/$wwwroot/g" $nginxConfigDir/sites-available/default
    sed -i "s/##BBC1ROOT##/$bbc1root/g" $nginxConfigDir/nginx.conf 
}

function check_nginx_install
{
    if ! 2>&1 $query nginx fcgiwrap libnginx-mod-rtmp >/dev/null; then
        echo "NGINX and/or rtmp, fcgiwrap modules not installed!"
        echo "Installing..."
        install_nginx
    else
        echo "Nginx, fcgiwrap and libnginx-mod-rtmp installed. Continuing..."
    fi
}

function install_nginx
{
    2>&1 $packager nginx libnginx-mod-rtmp fcgiwrap >/dev/null
}

function restart_nginx
{
    echo "Restarting Nginx..."
    systemctl restart nginx
}

echo "Beginning Burnsrv Setup..."

# Check environment

opsys=$(lsb_release -is)

echo "Detected OS: ${opsys}"

# We can copy HTML without root
if [ "$1" = "-w" ]; then
    copy_html
    exit 0
elif [ "$1" = "-h" ]; then
    echo -e $banner
    exit 0
fi

# Other ops need root/sudo
if [ $(id -u) -ne "0" ]; then
    echo "Please run as root or sudo."
    exit 1
fi

# We might want to just copy config
if [ "$1" = "-c" ]; then
    edit_config
    copy_config
    restart_nginx
    exit 0
fi

# Begin main body of script
check_os
if [ "$1" != "-p" ]; then
    check_ports
else
    echo "Skipping port check."
fi
check_nginx_install
copy_config
edit_config
create_dirs
copy_html
restart_nginx
