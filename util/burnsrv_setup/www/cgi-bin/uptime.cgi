#!/bin/bash

. common.sh

writeHeader

uptime -p | sed 's/up //' | sed 's/utes//' | tr -d '\n' 
