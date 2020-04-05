# csc3002_approximem

Source code repository for CSC3002: Evaluation of Applications on Approximate
Memories.

**Maintainer:** Mark Brown
**Contact:** mbrown49@qub.ac.uk

# Programming and Scripting Languages
* C
* Make
* Bash
* HTML
* Perl

# Repository Layout

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

## samples/

Sample images and binfiles for funfunct.

## contrib/
Any libraries that aren't authored by the maintainer. These however are
necessary to build some of the source. Currently empty.

## util/
Util contains all utility scripts that will assist us with running experiments
and any other future needs of this project.

### util/burnsrv_setup
Scripts that will assist setting up an NGINX streaming server. **See Readme there for details.**
Also contains scripts to conduct the streaming and HTML sources.

**Requirements**
Requires the BASH shell, nginx, ffmpeg and libnginx-mod-rtmp to run.

### util/testcfg

Note: Currently being rewritten. 

## [abandoned] mathlib/
An experimental maths library written in pure C. I planned to use it with functfun, but it wasn't necessary as C had its own built-in maths functions. However it wasn't a waste of time as it provided an opportunity to refresh my programming skills.
