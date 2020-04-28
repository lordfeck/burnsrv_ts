#!/usr/bin/perl
use Crypt::Digest::SHA256 ':all';
use CGI qw (param);
use File::chdir; #provides $CWD variable for manipulating working directory 

# MJB 28 04 2020
# TestHalter. Checks password and if we've a match the testrun is killed.

use warnings;
use feature ':5.10';

# EDIT THESE VALUES TO MATCH YOUR ENVIRONMENT
$testUser="mbrown49";
$testCfgDir="/home/$testUser/csc3002_approximem/util/testcfg/";
# SHA 256 Hashed Password
$hashWord="494a715f7e9b4071aca61bac42ca858a309524e5864f0920030862a4ae7589be";
# END USER-EDITED SECTION

# DEFINE FUNCTIONS

sub killTests {
    my $pid = fork;
    if ($pid) {
        print "Called killscript and testrunner with reset switch. Farewell, test run.";
    }
    elsif (defined $pid) {
        open STDIN,  '<', '/dev/null';
        open STDOUT, '>', '/dev/null'; # or point this to a log file
        open STDERR, '>&STDOUT';

        local $CWD=$testCfgDir;
        exec ("sudo -u $testUser ./killtestproc.sh") or say "Problem executing killtestproc.sh.";
        exec ("sudo -u $testUser ./testrunner.sh -r") or say "Problem launching testrunner.sh w/ reset switch.";
    }
    else {
        print "Failure creating process.";
    }

}

# The supplied password parameter
$passWord=param("passwd");

# passWord will not be set to this if we have the value from param().
unless ($passWord) {
    $passWord="WRONG";
}
chomp ($passWord);

$hashIn=sha256_hex($passWord);

# Begin HTML section
say "Content-type: text/html\n";

say "<html><head><title>Controlsrv Test Launcher.</title></head>";
say "<body>";
say "<h1>Test Launcher</h1>";

if ( $hashWord eq $hashIn ) {
    say "<h2>ACCESS GRANTED</h2>";
    say "<p>Now killing any test run in progress...</p>";
    killTests;
    say "<p>Check the previous page to track the test run status.</p>";
} else {
    say "Invalid Password";
}

say "<p><a href=\"../testcontrol.html\">Back</a></p>";
say "</body>";
say "</html>";
