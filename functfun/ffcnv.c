/* functfun conversion utility */
/* Authored: 22/01/2020 */
/* Author: MJB */

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include"fflib.h"
#include"ffglobals.h"

// Mode definitions
#define NONE 0
#define BINTOTXT 1
#define TXTTOBIN 2

int main (int argc, char** argv){
    char *banner = "FFCNV: Conversion utility.\n\
Usage: ffcnv -i <inputfile> -o <outputfile> <output format>\n\n\
Output Formats: -n biNary\n\
                -t Text";

    int mode=NONE; 
    char *inFileName = NULL;
    char *outFileName = NULL;
    float *logTable = NULL;
    int upperBound=-1;

    /* handle getopts */
    opterr=1;
    int thisArg;

    while ((thisArg=getopt(argc, argv, "hi:o:nt")) != -1){
        switch(thisArg){
            case'i':
                inFileName=optarg;
                #ifdef DEBUG
                fprintf(stderr, "Input file name: %s...\n", inFileName);
                #endif
                break;
            case'o':
                outFileName=optarg;
                #ifdef DEBUG
                fprintf(stderr, "Output file name: %s...\n", inFileName);
                #endif
                break;
            case'n':
                mode=TXTTOBIN;
                #ifdef DEBUG
                fprintf(stderr, "mode set as txttobin.\n");
                #endif
                break;
            case't':
                mode=BINTOTXT;
                #ifdef DEBUG
                fprintf(stderr, "mode set as bintotxt.\n");
                #endif
                break;
            // print help banner in these cases
            case'h':
                printf("%s\n", banner);
                exit(0);
            case'?':
                printf("%s\n", banner);
                exit(1);
            default:
                abort(); break;
        }
    }
    
    if (inFileName==NULL) {
        fprintf(stderr, "Missing input file. Cannot continue.\n");
        exit(1);
    }

    if (outFileName==NULL) {
        fprintf(stderr, "Missing output file. Cannot continue.\n");
        exit(1);
    }

    if (mode==NONE) {
        fprintf(stderr, "Conversion mode unset. Cannot continue.\n");
        exit(1);
    }
    
    // Now do the conversion.
    switch (mode) {
        case BINTOTXT:
            readInBin(inFileName, &logTable, &upperBound);
            fprintf(stderr, "Read in of %d logs from %s complete. Converting to text.\n", upperBound, inFileName);
            writeOutTxt(outFileName, logTable, upperBound);
            break;
        case TXTTOBIN:
            readInTxt(inFileName, &logTable, &upperBound);
            fprintf(stderr, "Read in of %d logs from %s complete. Converting to binary.\n", upperBound, inFileName);
            writeOutBin(outFileName, logTable, upperBound);
            break;
        default:
            fprintf(stderr, "Unexpected error.\n");
            break;
    }
    printf("Conversion from %s to %s complete.\n", inFileName, outFileName);
    return 0;
}
