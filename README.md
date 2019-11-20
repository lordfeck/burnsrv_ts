# csc3002_approximem

Source code repository for CSC3002: Evaluation of Applications on Approximate
Memories.

**Maintainer:** Mark Brown
**Contact:** mbrown49@qub.ac.uk

# Programming and Scripting Languages
* C
* Make
* Bash

*More TBD.*

# Repository Layout

## mathlib/
An experimental maths library written in pure C. Initially I thought to use it for
functfun but later settled for math.h. However time wasn't wasted as it served an
oppertunity to refresh my C knowledge.

**Usage:** run `make` then `./mathtest`

**Features**
* Euler's Number
* Natural Logs
* Exponential Function

See `mathops.h` for all implemented operations. Integer and double ops are
supported.

## functfun/
Short for 'Fun with Functions'. This can be configured to generate a log table
for any given range. The log table can be saved to disk or read from disk into
memory. The intention is that functfun will hold the values in memory while
the memory conditions are adjusted. Whence we can observe the effects of approx.
memory on the data.

The plan is to start simple with numbers. This should help familiarise me with
the testing procedures.

**Usage:** run `make run` to compile and run with default configuration.
`./fftest -h` gives a full overview of options

**Features**
* Generate log table for range
* Save log table to disk
* Read log table from disk
* Log tables are allocated directly to heap memory

## contrib/
Any libraries that aren't authored by the maintainer. These however are
necessary to build some of the source.

## util/
Util contains all utility scripts that will assist us with running experiments
and any other future needs of this project.

### util/testcfg
Configurable test suite scripts. Edit `testrun.config` to specify a test scenario.
Then execute `runexpt.sh` and it will execute the experiment according to your 
specification. Written in bash, intended for GNU/Linux.

A possible application is to have this run the aforementioned `functfun`
tool. We could also expand to include image, video, or any such other test.
It is intended that all aspects of environmental preparation and log
recording will be managed by these scripts.

** Requirements **
Requires the ubiquitous BASH shell.

** Usage ** 
Edit `testrun.config` to configure the test run.

Run `./functfun.sh` to execute the test run.

** Features **
* Configurable test runs
* May be extended to use any unix command-line utility
* Will support logging in an understandable format
