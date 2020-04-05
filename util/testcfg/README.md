# Test Runner README.

Test Runner will use the same config file as the other stream scripts.. Thence it learns which servers will be tested.

Test Runner will also use the config file found in `../makempeg/`. This tells it which video files are to be streamed.

## Assumptions:

* `tcpdump` is installed on both the local and remote systems.

* SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run0.

* The user account specified in `stream.config` should have `sudo` permissions *without* the need for a password.

* The interfaces on each server are specified in the classic Linux style. Namely: `eth0` opposed to `wlapshan3hj2h`. Also, the script uses `etho` as the capture interface for rtmp packets in tcpdump.

## Usage:

* Make sure config files are accurate.

* Run `./testrunner.sh`.

Further help and options are informed by running `./testrunner.sh -h`.

## Description of scripts:

### Greenwich.sh
This script ensures that the times on two hosts are exact. Uses ntpd and cron to accomplish this.

### startclient.sh
Use FFMPEG and stream a supplied rtmp stream to /dev/null. Used to create connections to a server.
