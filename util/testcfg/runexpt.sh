#!/bin/bash

# MJB 20 11 2019
# Execute test run as defined in testrun.config

. testrun.config
. logutil.sh

function runFFtest {
   echo "Running fftest..." 
   "$testExecDir"/fftest 
}

echo "Beginning Approximate Memory test run. The time is $(formattedDate)."

for theScenario in "$testScenario"; do
    case "$theScenario" in
        "fftest") runFFtest ;;
        * ) printFatalError "Unrecognised Test Scenario. Aborting test run." ;;
    esac
done

echo "$(formattedDate): Process complete."
