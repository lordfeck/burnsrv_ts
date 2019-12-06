#!/bin/bash

. common.sh

writeHeader

#uptime | tr -d ','| cut -d ' ' -f12-15
uptime |  awk -F 'load average:' '{ print $2 }' | tr -d ',' | tr -d '\n'
