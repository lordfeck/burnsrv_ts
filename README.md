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
