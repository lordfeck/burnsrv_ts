#!/usr/bin/perl

# Slogger: Slog through your logs
# Author: MJB Authored: 08/04/2020

use warnings;
use feature ':5.10';

package slogger;

$srvListPath="../testcfg/servers.csv";

say "Welcome to slogger!";

open (SRVLIST, "<", "$srvListPath") or die "Critical! Failed to open server list CSV!\n";

# First read them in
while ($line = <SRVLIST>) {
    ($hostname, $shortdesc, $longdesc) = split(",", $line);
    $servers{$shortdesc} = $hostname;
    $longDescs{$shortdesc} = $longdesc;
}

# Read them back to be sure it worked. (not quite right yet)
foreach $hostname (%servers) {
    say "$hostname";
}

close (SRVLIST);
