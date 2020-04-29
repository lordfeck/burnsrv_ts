#!/bin/bash

# List the contents of the Video on Demand directory.
# Author: MJB Authored: 29-04-2020

. common.sh
vodDir="/local/mbrown49/burnsrv/bbc1"

writeHeader "Burnsrv: Video Directory Listing"

wH "Video files available to stream:"
wP "$(ls $vodDir)"

wP '<a href="../index.html">Return to homepage</a>'

writeFooter
