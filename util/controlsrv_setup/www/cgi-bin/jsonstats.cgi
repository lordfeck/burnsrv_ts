#!/bin/bash
# New CGI that handles stats as JSON
# Author: MJB Authored: 06/12/19
. common.sh

writeJSONHeader

# CPU Usage in tenths of a percent
function getNginxCPU {
    ps --no-headers -C nginx -o cp | awk '{cp += $1} END {print cp}'
}
# PS returns perc of CPU time / time program has been running.
function getNginxCPUPerc {
    ps --no-headers -C nginx -o %cpu | awk '{cpu += $1} END {print cpu}'
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

# Resident set size; total of process in memory
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

jT "nginxCPU"
jF "$(getNginxCPU)" 

jT "nginxCPUPerc"
jF "$(getNginxCPUPerc)" 

jT "nginxRssKb"
jF "$(getNginxRSS)" "f"

echo "}"
