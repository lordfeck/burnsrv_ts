/* FFcmp; read in binfiles and calculate no. of errors
 * Authored: 20/01/2020
 *
 */

#include<stdlib.h>
#include<stdio.h>

#include"ffglobals.h"
#include"fftest.h"
#include"ffcmp.h"

int main (int argc, char** argv)
{
    char *banner = "FFCmp: Binary comparison utility.";
    printf("%s\n", banner);
    
    //TODO: Replace with array for filenames
    char *filename1, *filename2;
    // TODO: replace with arrays also... we'll let the user supply as many files
    // count them up and allocate.
    float *logTable1, *logTable2;
    int upperBound1, upperBound2;

    if (argc <2) {
        puts("Two arguments required. Go and have two rows with a political opposite.");
        exit(1);
    }

    puts("Reading in file 1...");
    readInBin(filename1, &logTable1, &upperBound1);
    printf("Read in %d logs from %s.\n", upperBound1, filename1);

    return 0;
}
