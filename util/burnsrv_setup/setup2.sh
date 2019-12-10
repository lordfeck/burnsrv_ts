#!/bin/bash

# APRROXIMATE MEMORIES SETUP SCRIPT
# V1.2-short 06-12-2019
# Author: MJB Authored: 04-12-19

##### EDIT BETWEEN THESE LINES TO HAVE MATCHING PATHS ####
readonly rootDir="/local/mbrown49/burnsrv"
readonly vidDir="/local/mbrown49/burnsrv/bbc1/"
readonly htmlDir="/local/mbrown49/burnsrv/www/"
# These need pathnames escaped for SED.
readonly bbc1root='\/local\/mbrown49\/burnsrv\/bbc1'
readonly wwwroot='\/local\/mbrown49\/burnsrv\/www'
readonly userName="mbrown49"
##########################################################

readonly nginxConfigDir="/etc/nginx/"
readonly rtmpEnabled="/etc/nginx/modules-enabled/50-mod-stream.conf"

readonly banner="setup2.sh: Use -w to copy just WWW\nUse -c to copy just config.\nRun with no flags to perform a full install."

function install_rtmp
{
    echo "Installing ARM-compiled rtmp module."
    cp -rfv modrtmp-arm/ngx_rtmp_module.so /usr/lib/nginx/modules/ngx_rtmp_module.so
    cp -rfv modrtmp-arm/mod-stream.conf /usr/lib/nginx/modules/modules-available/mod-stream.conf
    touch $rtmpEnabled
    ln -sv /usr/share/nginx/modules-available/mod-stream.conf $rtmpEnabled
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

    echo "Setting ownership for $userName on $htmlDir."
    chown -R $userName $htmlDir
}

function edit_config
{
    echo "Editing config files with correct WWWroot."
    sed -i "s/##WWWROOT##/$wwwroot/g" config/default
    sed -i "s/##BBC1ROOT##/$bbc1root/g" config/nginx.conf 
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
    edit_config
    copy_config
    restart_nginx
    exit 0
elif [ "$1" = "-h" ]; then
    # display help
    echo -e $banner
    exit 0
fi

# Begin main body of script
edit_config
copy_config
create_dirs
copy_html
install_rtmp
restart_nginx
