# Test Runner README.

Test Runner will use the same config file as the other stream scripts.. Thence it learns which servers will be tested.

Test Runner will also use the config file found in `../makempeg/`. This tells it which video files are to be streamed.

## Assumptions:

* `tcpdump` is installed on both the local and remote systems.

* SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run0.

* The user account specified in `stream.config` should have `sudo` permissions *without* the need for a password.

* The interfaces on each server are specified in the classic Linux style. Namely: `eth0` opposed to `wlapshan3hj2h`. Also, the testrunner script uses `eth0` as the capture interface for rtmp packets in tcpdump.

## Usage:

* Make sure config files are accurate.

* Run `./testrunner.sh`.

Further help and options are informed by running `./testrunner.sh -h`.

## Description of other scripts:

### greenwich.sh
This script ensures that the times on two hosts are exact. Uses crony (ntp daemon) and cron to accomplish this.

* Call with "-s" just to sync. The testrunner does this.

* Call with no args to sync times and compare the system clocks of all hosts specified in `stream.config`.

### startclient.sh
Use FFMPEG and stream a supplied rtmp stream to /dev/null. Used to create connections to a server.

### livestream.sh
Use FFMPEG to stream MP4 video files live to rtmp. This is the same as broadcasting from your home PC and using the server to relay towards many hosts. We haven't used this method for the experiment; rather the chosen vod method is implemented in `startclient.sh`.
