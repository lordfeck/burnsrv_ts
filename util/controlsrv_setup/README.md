# controlsrv setup

Setup files that will build a controlsrv. The controlsrv is responsible for testing, monitoring and reporting the results of streaming experiments.

## Requirements
Requires the BASH shell, nginx, fcgiwrap, ffmpeg and a number of Perl modules to function fully. Check  the *dependencies* variable inside `setup.config`.

## Script Features

### setup.sh

This script will fully install a controlsrv machine.

* Check that ports 80 and 1935 are free
* Setup Nginx (if not already installed)
* Installs fcgiwrap.
* Create dirs for both HTML and scripts, then copies these across.
* Install nginx config.
* Link the testrunner's results dir with a path in the htdocs.
* Launch the server.

**Usage**

Run `./setup.sh` to setup on a "dev" environment. This setup method uses your login name and other params relevant to the local developer's machine.

Run `./setup.sh -l` to setup on a "live" environment. This setup method uses the login name and other params relevant to a remote machine.

Call `./setup.sh -h` to see all setup options listed.

The script should be run either with `sudo` or using `root`.


### Also contains

Basic CGI scripts to monitor system health. These CGIs also report whether a test is currently running and the latest results from any currently-underway test run.

Perl Script that checks for a password. If the password is valid, then a test is "kicked off" using the same `testrunner.sh` script and configuration inside `../testcfg/`.


