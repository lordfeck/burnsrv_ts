#Test Runner README.

Test Runner will use the same config file as the `../burnsrv_setup/` utilities. Thence it learns which servers will be tested.

Test Runner will also use the config file found in `../makempeg/`. This tells it which video files are to be streamed.

## Assumptions:

`tcpdump` is installed on both the local and remote systems.

## Usage:

* Make sure config files are accurate.

* Run `./testrunner.sh`.

Further help and options are informed by running `./testrunner.sh -h`.
