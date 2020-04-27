# burnsrv setup

Setup files that will build a streaming server. Also utility scripts to run a streaming server.

**Burn:** *noun*, Ulster-Scots word meaning 'stream' or 'brook'. Also refers to what
happens to the RAM during these experiments.

## Requirements
Requires the BASH shell, nginx, fcgiwrap and libnginx-mod-rtmp to run. Other dependencies are checked and installed during the script's execution.

## Script Features

### setup.sh

This script will fully install a burnsrv machine.

* Check that ports 80 and 1935 are free
* Setup Nginx (if not already installed)
* Install the RTMP mod (if not already installed)
* Installs fcgiwrap.
* Create dirs for HTML, video and CGI.
* Install nginx config and HTML files
* Launch the server

**Usage**

Run `./setup.sh` to setup on a "dev" environment. This setup method uses your login name and other params relevant to the local developer's machine.

Run `./setup.sh -l` to setup on a "live" environment. This setup method uses the login name and other params relevant to a remote machine.

Call `./setup.sh -h` to see all setup options listed.

The script should be run either with `sudo` or using `root`.


### Also contains

Basic CGI scripts to monitor system health. These may be visited by the web server.
Nginx also has a handy inbuilt tool to report stream statistics. This is also enabled by default.

