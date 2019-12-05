# burnsrv setup

Burn: noun, Ulster-Scots word meaning 'stream' or 'brook'. Also refers to what
might happen our memory.

## Script Features

`setup.sh`

* Check that ports 80 and 1935 are free
* Setup Nginx (if not already installed)
* Install the RTMP mod (if not already installed)
* Install nginx config and HTML files
* Launch the server

`setup2.sh`

* Handles copying of files without any installation or preinstallation checks

Compatible with Debian and Red Hat/CentOS package managers. Uses nginx and systemd.

**Also contains:** Basic CGI scripts to monitor system health. These may be visited by the web server.
Nginx also has a handy inbuilt tool to report stream statistics. This is also enabled by default.

Eventually I hope to monitor async system health with JavaScript requests in the browser. It isn't difficult
to make plain asynch GET requests, so this will give the project a nice touch.
