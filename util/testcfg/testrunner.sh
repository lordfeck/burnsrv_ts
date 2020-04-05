#!/bin/bash

# Test Runner master script
# by MJB, 05/04/2020

# test for local presence of tcpdump
if ! which tcpdump >/dev/null; then
    echo "Tcpdump is not installed. Cannot continue." 1>&2
    exit 1
fi

