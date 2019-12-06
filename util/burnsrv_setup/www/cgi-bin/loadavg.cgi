#!/bin/bash

. common.sh

writeHeader

uptime | tr -d ','| cut -d ' ' -f12-15
