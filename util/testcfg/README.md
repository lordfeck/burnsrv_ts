# Test Runner README.

Run configured streams across each test server. This script may be run locally or run from a configured `controlsrv`. 

The name of the main test runner script is `testrunner.sh`. Normally, it is the **only script** that should be executed by a user.

When run, the script cycles through each server and each video parameter. For each of these, the video is streamed to `/dev/null`. The total time in ms is recorded, as is the average ping and the total number of packets sent and received by the host. The result of each of these is written to a CSV file for analysis elsewhere.

## Usage:

* Make sure config files are accurate.

* Run `./testrunner.sh`. This will carry out all the configured tests.

* Alternatively, connect to the server using a web browser and use use the Web UI's "Test Control" section to launch the tests.

* Output CSV will be found (by default) in the `./results/` directory.

* You may run `./testrunner.sh -r` to reset the test environment.

## Assumptions:

* `tcpdump` is installed on both the local and remote systems.

* `ffmpeg` is installed on the local system.

* SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run.

* The user account specified in `stream.config` should have `sudo` permissions *without* the need for a password.

## Description of Config Files.

### stream.config

Main configuration file for a test run. You'll be concerned mostly with the "Testrunner Configuration" and the "Testrun Parameters" sections.

Most of the defaults in *Testrunner Configuration* should be acceptable. Likely, you'll want to edit the "localUser" and "localIface" options to match your local system.

Testrun Parameters likely will be of greater interest. Here, you may set the file name for each video file to be streamed, then each quantisation level, then each resolution. Additionally, a variety of lengths may be specified. Testrunner will stream each file from each server with each parameter. This will be illustrated clearly with a practical example.

**Default TestRun Parameter examples:**

    streamFiles=(
        "tractor"
        "islands"
        "bunny"
    )
    
    lengths=( "00:25" "01:00" "02:00" "04:00" )
    quants=("23" "26" "32")
    resolutions=("854x480" "1280x720" "1920x1080")

The above configuration, when run across three hosts, results in a total of 324 video streams. 

The expected video format on each remote host is: `$vid-$quant-$res.$streamContainer`, e.g. `tractor-26-1280x720.mp4`. It should be obvious how the above arrays become parameters in the `testrunner.sh` script.

It is important to follow the conventions exactly. The compainion `../makempeg/makempeg.sh` script will use this same config file to call ffmpeg and render each video with each parameter. This way, the filename conventions and records will match exactly.

### servers.csv
A simple CSV file listing each remote burnsrv host. We assume that each host on this list has the burnsrv code checked out and `../burnsrv_setup/setup.sh` was completed successfully.

The format for each entry is as follows: `HOSTNAME, SHORT DESCRIPTION, LONG DESCRIPTION, IFACE NAME`. Example: `qub-streamer.thran.uk,az-x86,Azure x86,eth0`.

* The *hostname* is used for both RTMP and SSH connections.
* The *short description* is used in filenames and should use **no spaces**.
* The *long description* is just for reference, a fuller name or notes for the server.
* The *iface name* should be the external interface name. This is the interface through which RTMP traffic will flow. Remote tcpdump requires this.

## CSV Results File Description.

Each line in the results CSV follows the exact format:

`vidfile, shortdesc, clientcount, streamlength, quant, res, streamtime, total packet count, avgping`. 

Example: `tractor,az-x86,1,00:25,23,854x480,21466311254,6817,21.734`

* The *streamtime* is in NS and may be converted to MS through dividing by 1,000,000.
* The *client count* means the number of local clients simultaneously streaming from this host. Currently, it should only be 1.

The rest of the parameters are either described already or need no elaboration.

## Description of other scripts:

### killtestproc.sh
Call this to kill any testrunner.sh processes currently running. Best practice is to execute this before executing `testrunner.sh -k` to reset the environment.

### greenwich.sh
This script ensures that the times on two hosts are exact. Uses crony (ntp daemon) and cron to accomplish this. Includes a helper script for sync validation, `gpolltime.sh`.

* Call with "-s" just to sync. The testrunner does this.

* Call with no args to sync times and compare the system clocks of all hosts specified in `stream.config`.

* Optionally, using Greenwich a cron job may be set to call `gpolltime.sh` on each host after a minute. This records the exact time on each host. Then these times are collected and compared. Thereby, the time sync may be validated.

### startclient.sh
Use FFMPEG and stream a supplied rtmp stream to /dev/null. Used extensively inside `testrunner.sh` and shouldn't be run directly, development purposes notwithstanding.

### livestream.sh
Use FFMPEG to stream MP4 video files live to rtmp. This is the same as broadcasting from your home PC and using the server to relay towards many hosts. We haven't used this method for the experiment; rather the chosen vod method is implemented in `startclient.sh`.
