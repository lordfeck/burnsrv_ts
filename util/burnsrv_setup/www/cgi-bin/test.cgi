#!/bin/bash

# BASH CGI TEST
# Author: MJB Authored: 06-12-2019

. common.sh

writeHeader "the world of bash beckons"

wH 'bash made this'

wP "Hello from $(whoami)"

wP "$(uptime)"

wP "$(uname -a)"

wH "Envrionment Variables:" "2"
wP "$(/usr/bin/env)"

wH 'Looks very well to me.' "2"
wP "Test over."

writeFooter
