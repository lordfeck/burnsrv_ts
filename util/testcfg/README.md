# Test Runner README.

Test Runner will use the same config file as the other stream scripts.. Thence it learns which servers will be tested.

Test Runner will also use the config file found in `../makempeg/`. This tells it which video files are to be streamed.

## Assumptions:

* `tcpdump` is installed on both the local and remote systems.

* SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run SSH keys have been copied from the local to all remote systems. Passwordless SSH logins must be possible for the experiment to run0.

## Usage:

* Make sure config files are accurate.

* Run `./testrunner.sh`.

Further help and options are informed by running `./testrunner.sh -h`.
