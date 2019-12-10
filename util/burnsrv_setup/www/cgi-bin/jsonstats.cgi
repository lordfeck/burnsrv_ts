#!/bin/bash
# New CGI that handles stats as JSON
# Author: MJB Authored: 06/12/19
. common.sh

writeJSONHeader

function calculateRSS {
    echo -n "dear only knows"
}

function calculateCPU {
    echo -n "havnae a clue"
}
echo "{"

jT "rss"
jF "$(calculateRSS)"

jT "procCPU"
jF "$(calculateCPU)" "f"

echo -n "}"
