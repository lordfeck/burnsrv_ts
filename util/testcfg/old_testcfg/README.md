
### util/testcfg

Deprecated idea for test runs.

Configurable test suite scripts. Edit `testrun.config` to specify a test scenario.
Then execute `runexpt.sh` and it will execute the experiment according to your 
specification. Written in bash, intended for GNU/Linux.

A possible application is to have this run the aforementioned `functfun`
tool. We could also expand to include image, video, or any such other test.
It is intended that all aspects of environmental preparation and log
recording will be managed by these scripts.

**Requirements**

Requires the ubiquitous BASH shell to be installed.

**Usage** 

Edit `testrun.config` to configure the test run.

Run `./runexpt.sh` to execute the test run.

**Features**
* Configurable test runs
* May be extended to use any unix command-line utility
* Will support logging in an understandable format
