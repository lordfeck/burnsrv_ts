#!/usr/bin/perl
use Crypt::Digest::SHA256 ':all';
use CGI qw (param);
use File::chdir; #provides $CWD variable for manipulating working directory 

# MJB 21 04 2020
# TestLauncher. Checks password and whether a test is already running.
# If conditions are right another test run is begun.
# Help from: https://stackoverflow.com/a/7019142 and https://stackoverflow.com/a/10518970

use warnings;
use feature ':5.10';

$testUser="mbrown49";
$testCfgDir="/home/$testUser/csc3002_approximem/util/testcfg/";
$testFlag="/home/$testUser/.testrunning";

# DEFINE FUNCTIONS
sub launchTests {
    my $pid = fork;
    if ($pid) {
        print "Testrunner process has been launched!";
    }
    elsif (defined $pid) {
        open STDIN,  '<', '/dev/null';
        open STDOUT, '>', '/dev/null'; # or point this to a log file
        open STDERR, '>&STDOUT';

        local $CWD=$testCfgDir;
        exec ("sudo -u $testUser ./testrunner.sh") or say "Problem launching testrunner.sh.";
        exec(@cmd);
    }
    else {
        print "Testrunner failed to launch!";
    }

}

# SHA 256 Hashed Password
$hashWord="494a715f7e9b4071aca61bac42ca858a309524e5864f0920030862a4ae7589be";

# The supplied password parameter
$passWord=param("passwd");

# For testing, will not be set if we have the param value.
unless ($passWord) {
    $passWord="changeme123";
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
    say "<p>Now launching the configured test run...</p>";
    if ( -e $testFlag ) {
        say "<p>Sorry, I'm afraid I cannot do that: <b>A test is already running</b> (or exited improperly), please check manually.</p>";
    } else {
        launchTests;
        say "<p>Check the previous page to track the test run status.</p>";
    }
} else {
    say "Invalid Password";
}

say "<p><a href=\"../testcontrol.html\">Back</a></p>";
say "</body>";
say "</html>";
