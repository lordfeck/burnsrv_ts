#!/usr/bin/perl

# Slogger: Slog through your logs
# Author: MJB Authored: 08/04/2020

use warnings;
use feature ':5.10';

package slogger;

# DEFINE GLOBAL VARS
glob $srvListPath="../testcfg/servers.csv";
glob $tcpdTxtDir="/tmp/";
glob $resultsFolder="../testcfg/results/";
glob @servers;
glob @srvdesc;
glob @packetTimes;

# Life would be nice if I could make slogger read stream.config and grab this value.
glob $capDir="../testcfg/tcpdumps/";

# DEFINE SUBROUTINES
sub dumpTcpDump {
    # Convert tcpdump to text
    system "2>&- tcpdump -r $capDir/@_ > $tcpdTxtDir/@_.txt";

    unless ( -T "$tcpdTxtDir/@_.txt" ){
        die "tcpdump text file missing! Check permissions for $tcpdTxtDir.";
    }
}

sub readInServerList {
    open (SRVLIST, "<", "$srvListPath") or die "Critical! Failed to open server list CSV!\n";

    while ($line = <SRVLIST>) {
        chop($line);
        ($hostname, $shortdesc, $longdesc) = split(",", $line);
        $servers{$shortdesc} = $hostname;
        $srvdesc{$shortdesc} = $longdesc;
    }
    close (SRVLIST);
}

#eventually will be some kind of array
sub readTcpTxt {
    open (TCPTXT, "<", "$tcpdTxtDir/@_.txt") or die "Can't open @_.txt";
    $line = <TCPTXT>;
    chop($line);
    say "Debug: Line is... $line.";
    @linearray = split(" ", $line);
    $packetTimes[0] = $linearray[0];
    close TCPTXT;
#    return $line =~ /^\d{2}:\d{2}:\d{2}\.\d{6}\s+/;
}

# BEGIN MAIN EXECUTION
say "Welcome to slogger!";

readInServerList();

# Read them back to be sure it worked.
say "Server list and information:";
foreach $shortdesc (keys %servers) {
    say "$shortdesc is $servers{$shortdesc}. Notes: $srvdesc{$shortdesc}.";
}

dumpTcpDump("qub-streamer.thran.uk.local");
dumpTcpDump("qub-streamer.thran.uk.remote");

say "Extracted dumpfiles to /tmp, now parsing...";

readTcpTxt("qub-streamer.thran.uk.local");
say "Time 0 is: $packetTimes[0]";

# do some calculations

# output to csv

# send to charttopper.pl

