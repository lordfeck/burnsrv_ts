# burnsrv setup

Setup files that will build a burnsrv, or streaming server.

**Burn:** *noun*, Ulster-Scots word meaning 'stream' or 'brook'. Also refers to what
happens to the RAM during some experiments.

## Requirements
Requires the BASH shell, nginx, fcgiwrap and libnginx-mod-rtmp to run. Other dependencies are checked and installed during the script's execution.

It is recommended to install your burnsrv onto Debian or its derivative Ubuntu. Some required libraries (notably nginx-rtmp) are not available ready-built on CentOS.

The setup script will query your packager for dependencies. On recent Debian (10+) and Ubuntu (18.04+) versions all dependencies are available in the OS maintainer's repository.

## Description of Directories.

* `./config/` configuration files used by nginx. Copied and modified by *setup.sh*.
* `./www/` HTML and CGI sources. Both are copied to the specified WWW-root by *setup.sh*.
* `./bbc1/` RTMP video directory. The video files stored therein are streamed by `../testcfg/testrunner.sh` during a test run. Default contains one MP4 sample, duck.mp4.


## Setup Script Features

The `setup.sh` script will fully install a burnsrv machine.

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

Basic CGI scripts to monitor system health. These may be visited by the web server. Stored in `./www/cgi-bin/`
Nginx also has a handy inbuilt tool to report stream statistics. This is also enabled by default.

