#!/bin/bash
# New CGI that handles stats as JSON
# Author: MJB Authored: 06/12/19
. common.sh

writeJSONHeader

function calculateRSS {
    echo -n "SOON"
}

function calculateCPU {
    echo -n "ALSO SOON"
}

function getUptime {
    uptime -p | sed 's/up //' | sed 's/utes//' | tr -d '\n' 
}

function getTotalMem {
    free -m | grep Mem | awk '{ print $3 }' | tr -d '\n'
}

function getLoadAvg {
    uptime |  awk -F 'load average:' '{ print $2 }' | tr -d ',' | tr -d '\n'
}

function getNginxRSS {
    ps --no-headers -C nginx -o rss |  awk '{rss += $1} END {print rss}'
}

# Begin JSON composition
echo "{"

jT "uptime"
jF "$(getUptime)"

jT "totalMem"
jF "$(getTotalMem)"

jT "loadAvg"
jF "$(getLoadAvg)"

jT "rss"
jF "$(calculateRSS)"

jT "procCPU"
jF "$(calculateCPU)" 

jT "nginxRssKb"
jF "$(getNginxRSS)" "f"

echo "}"
