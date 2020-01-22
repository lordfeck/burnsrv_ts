/* FFcmp; read in binfiles and calculate no. of errors
 * Authored: 20/01/2020
 *
 */

#include<stdlib.h>
#include<stdio.h>

#include"ffglobals.h"
#include"fflib.h"
#include"ffcmp.h"

float calculateErrorRate(int baseDiff, int upperBound);
int calculateBaseDiff(float *logTable1, float *logTable2, int upperBound);

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
    int baseDiff;

    printf("Argc: %d\n", argc);

    if (argc <2) {
        puts("Two arguments required. Go and have two rows with a political opposite.");
        exit(1);
    }

    // temp measure, make filename pointer to arg
    filename1=argv[1];
    filename2=argv[2];

    puts("Reading in file 1...");
    readInBin(filename1, &logTable1, &upperBound1);
    printf("Read in %d logs from %s.\n", upperBound1, filename1);
    readInBin(filename2, &logTable2, &upperBound2);
    printf("Read in %d logs from %s.\n", upperBound1, filename1);

    if (upperBound1!=upperBound2) {
        fprintf(stderr, "Mismatch between log boundaries %d!=%d. (NOT YET) Using the lesser for both.\n", upperBound1, upperBound2);
        exit(1);
    }

    baseDiff=calculateBaseDiff(logTable1, logTable2, upperBound1);
    printf("Calculated base diff: %d \n", baseDiff);

    return 0;
}

int calculateBaseDiff(float *logTable1, float *logTable2, int upperBound) {
    int baseDiff=0;
    for (int i=0; i<upperBound; i++) {
        if(logTable1[i]!=logTable2[i]) baseDiff++;
    }
    return baseDiff;
}

