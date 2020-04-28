#!/bin/bash

echo "Killing all testrunner.sh processes."
sudo kill -2 `pgrep testrunner.sh` 2>&1 >/dev/null
