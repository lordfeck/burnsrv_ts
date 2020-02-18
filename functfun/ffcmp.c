/* FFcmp; read in test files and calculate no. of errors
 * Authored: 20/01/2020
 * Author: MJB
 */

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h> //getopt

#include"ffglobals.h"
#include"fflib.h"
#include"ffcmp.h"

int main(int argc, char** argv) {
    char *banner = "FFCmp: Binary comparison utility.\nUsage: ffcmp <mode> <base file> <list of files>\n\n\
Note: all later files are compared against the first base file. It should be the original and unaltered.\n\
Later files should be the output of either fftest or ffimg.\n\n\
Modes:\n\
-f Use binfiles of floating point numbers, get a numeric comparison\n\
-b use byte mode (for images and anything else)\n\
-h show help and exit\n";
    
    char *filename1, *filename2;
    float *logTable1, *logTable2;
    int upperBound1, upperBound2, upperBound;
    int baseDiff, fcount;
    float errorFraction;
    int mode=-1;

    /* handle getopts */
    opterr=1;
    int thisArg=0;

    while ((thisArg=getopt(argc, argv, "hfb")) != -1){
        switch(thisArg){
            case'f':
                mode=FLOAT_MODE; 
                break;
            case'b':
                mode=BYTE_MODE;
                break;
            case'h':
                printf("%s", banner);
                exit(0);
        }
    }

    if (mode==-1) {
        fprintf(stderr, "Mode unselected. Cannot continue.\n%s", banner);
        return 1;
    }
    
    fcount=argc-optind;
    
    if(fcount<2) {
        fprintf(stderr, "Please supply a base file and a list of comparison files (minimum 1 comparison).\n");
        return 2;
    }

#ifdef DEBUG
printf("optind:%d\n", optind);
printf("argc:%d\n", argc);
#endif

    switch (mode){
        case FLOAT_MODE:
            puts("Using float mode...");
            compareFloats(fcount, argc, argv);
            return 0;
            break;
        case BYTE_MODE:
            puts("Not yet ready.");
            return 1;
            break;
        default:
            return 1;
    }

    return 0;
}

/* Returns base diff, i.e. number of entries that are not equal */
int calculateBaseDiff(float *logTable1, float *logTable2, int upperBound) {
    int baseDiff=0;
    for (int i=0; i<upperBound; i++) {
        if(logTable1[i]!=logTable2[i]) {
            #ifdef DEBUG
            printf("Mismatch at index %d. %f is not %f.\n", i, logTable1[i], logTable2[i]);
            #endif
            baseDiff++;
        }
    }
    return baseDiff;
}

float calculateErrorFraction(int baseDiff, int upperBound) {
    float fract=((float)baseDiff/(float)upperBound);
#ifdef DEBUG
    printf("debug: calculated error fraction is %5.2f, basediff was %d and upperbound was %d.\n", fract, baseDiff, upperBound);
#endif
    return fract;
}

int returnLowerBound(int upperBound1, int upperBound2){
    if (upperBound1 < upperBound2) {
        return upperBound1;
    } else {
        return upperBound2;
    }
}

int compareFloats(int fcount, int argc, char** argv){
    // first allocate an array of pointers to the float log tables
    float *logTables[fcount];
    // store the upperBounds read in from files
    int upperBounds[fcount];
    int argOffset = argc-fcount;
    float errorFraction;
    // store the base diffs (first file is base, later files are compared against)
    int baseDiffs[fcount];
    baseDiffs[0]=0;
    int avgBaseError=0;
    float avgBaseFraction=0.0;
    // compare each table against its neighbour
    int adjacentDiffs[fcount];
    int avgAdjError=0;

    // cycle through the non-getopts arguments, they are files to be read in
    for (int i=0; i<fcount; i++){
        readInBin(argv[i+argOffset], &logTables[i], &upperBounds[i]);
        fprintf(stderr, "Read in %d logs from %s.\n", upperBounds[i], argv[i+argOffset]);
    }

    // check upper bounds match
    for (int i=1; i<fcount; i++){
       if (upperBounds[0] != upperBounds[i]){
            fprintf(stderr, "Mismatch in upper bounds for file %d, cannot continue.\n", i);
            exit(1);
        }
    }
    
    // calculate error rate and percentage
    printf("Base difference compared against %s.\n", argv[argOffset]);

    for (int i=1; i<fcount; i++){
        // we use upperBounds[0] for all because they were already checked to match
        baseDiffs[i]=calculateBaseDiff(logTables[0], logTables[i], upperBounds[0]);
        printf("Base difference for %s: %d \n", argv[argOffset+i], baseDiffs[i]);
        errorFraction=calculateErrorFraction(baseDiffs[i], upperBounds[0]);
        printf("Error Percentage for %s: %5.2f\n", argv[argOffset+i], errorFraction*100.0);
    }

    // calculate average base rate and error percentage (merge with above loop?)
    for(int i=0; i<fcount; i++){
        avgBaseError+=baseDiffs[i];
#ifdef DEBUG
        printf("Iteration: %d AvgBaseError: %d AvgBaseFraction: %f\n", i, avgBaseError, avgBaseFraction);
#endif
    }

    avgBaseError=avgBaseError/fcount;
    avgBaseFraction=calculateErrorFraction(avgBaseError,upperBounds[0]);

    printf("Average base difference: %d\n", avgBaseError);
    printf("Average error percentage: %5.2f\n", avgBaseFraction*100.0);

    puts("TODO: Adjacent difference.");

    // housekeeping
    for (int i=0; i<fcount; i++) free(logTables[i]);
}

