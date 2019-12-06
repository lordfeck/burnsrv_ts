#!/bin/bash
# Prints used memory in MB.
# Used memory (calculated as total - free - buffers - cache)
. common.sh

writeHeader

free -m | grep Mem | awk '{ print $3 }' | tr -d '\n'
