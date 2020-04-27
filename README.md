# csc3002_approximem

Source code repository for CSC3002: Evaluation of Applications on Approximate
Memories.

**Maintainer:** Mark Brown
**Contact:** mbrown49@qub.ac.uk

# Programming and Scripting Languages
* C
* Make
* Bash
* HTML/CSS/Js
* Perl

# Repository Layout
For each subsection, a readme file details its purpose and usage in greater depth.

## util/
Util contains all utility scripts that will assist us with installing servers and running tests using these servers.

### util/burnsrv_setup
Scripts that will assist setting up an NGINX RTMP streaming server.

### util/controlsrv_setup
Installation script for a testing and reporting server. Allows the choice of either a Web UI or Command Line Interface to launch tests. 

### util/testcfg
*This section should be considered the meat and bones of this project.* Testcfg contains the `testrunner.sh` script which launches a set of streams, as configured inside `stream.config`. The readme file therein comprehensively documents its functions.

There are also scripts to assist with time syncing across each host.

### util/makempeg
A script that uses FFmpeg to batch convert a video file into formats required by the tests.

### util/slogger
A Perl script to analyse results from testrunner and calculate graphs and statistics. [not complete].


## functfun/ [partially complete]
Short for 'Fun with Functions'. This can be configured to generate a table of logarithms
for any given range. The log table can be saved to disk or read from disk into
memory. The intention is that functfun will hold the values in memory while
the memory conditions are adjusted. Whence we can observe the effects of approx.
memory on the data.

The plan is to start simple with numbers. This should help familiarise me with
the testing procedures.

**Usage:** run `make run` to compile and run with default configuration.
`./fftest -h` gives a full overview of options

**Features**
* Generate logarithm table for range
* Save logarithm table to disk
* Read logarithm table from disk
* Logarithm tables are allocated directly to heap memory

The same is also possible for JPEG image files.

Conversion of binary logarithim tables to/from text format is possible using the utility `ffcnv`.

**Note:** Funfunct is mostly functional, but there are bugs. Not fully realised.

## samples/

Sample images and binfiles for funfunct.

## contrib/
Any libraries that aren't authored by the maintainer. These are
necessary to build some of the source. Currently empty.


