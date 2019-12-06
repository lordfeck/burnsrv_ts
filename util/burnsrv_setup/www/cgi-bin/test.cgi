#!/bin/bash

# BASH CGI TEST
# Author: MJB Authored: 06-12-2019

. common.sh

writeHeader

echo '<html><head><title>the world of bash beckons</title></head>'

wH 'bash made this'

wP "Hello from $(whoami)"

wP "$(uptime)"

wP "$(uname -a)"

wH 'Looks very well to me.' "2"
wP "Test over."

echo '</html>'
