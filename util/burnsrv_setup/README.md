# burnsrv setup

Setup files that will build a streaming server. Also utility scripts to run a streaming server.

**Burn:** *noun*, Ulster-Scots word meaning 'stream' or 'brook'. Also refers to what
might happen our memory.

## Requirements
Requires the BASH shell, nginx, systemd, ffmpeg and libnginx-mod-rtmp to run.

## Script Features

### setup.sh

* Check that ports 80 and 1935 are free
* Setup Nginx (if not already installed)
* Install the RTMP mod (if not already installed)
* Install nginx config and HTML files
* Launch the server

**Usage**

Run `./setup.sh`

### setup2.sh

Setup script intended for the x-gene machine.

* Handles copying of files without any installation or preinstallation checks
* By default will attempt to install an ARM-compiled libnginx-mod-rtmp

**Usage**

`make armzip` and copy the zip file to the ARM system.

Install nginx manually. Then run `./setup2.sh`

### startstream.sh

Script that serves as the frontend to ffmpeg.

* Run a stream as configured in `stream.config`
* Run a stream as configured from command line args

**Usage**

Edit configuration inside `stream.config`

Run `./startstream.sh`

Also see `./startstream.sh -h` for help.


### Also contains

Basic CGI scripts to monitor system health. These may be visited by the web server.
Nginx also has a handy inbuilt tool to report stream statistics. This is also enabled by default.

Eventually I hope to monitor async system health with JavaScript requests in the browser. It isn't difficult
to make plain asynch GET requests, so this will give the project a nice touch.
