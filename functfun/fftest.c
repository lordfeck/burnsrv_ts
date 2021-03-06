/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 03/11/2019 */
/* Funct Fun Test */
/* Generate a large log table: */
/* Dump it in a text file or put it in RAM as you desire.*/
/* The previous functions of this file are handeled by ffgen.c */
/*****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#include"ffglobals.h"
#include"fflib.h"
#include"fftest.h"

/** BEGIN IMG SRC for MERGE ***/


/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 06/02/2020 */
/* Funct Fun with Images */
/*****************************************************************************/

/*
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#include"ffglobals.h" // READIN_BUFFER, imgFile typedef
#include"fflib.h"

int main(int argc, char** argv){
    char *banner="ffimg: Hold image in memory, dump at regular intervals.\n\
Usage:\n\
./ffimg <inputFileName> <outputFileName> <time (s)> <interval>";

    char *buffer = NULL; 
    char *inFileName = NULL;
    char *outFileName = NULL;
    FILE *inFile = NULL;
    size_t bytes;
    int maxTime, interval;

    imgFile workingImage;

    /* handle args */
    if (argc <5){
        fprintf(stderr, "%s\n", banner);
        return 1;
    }

    inFileName = argv[1];
    outFileName = argv[2];
    maxTime = atoi(argv[3]);
    interval = atoi(argv[4]);
    
    if (maxTime <= 0 || interval <=0){
        puts("Interval or maxtime invalid.");
        return 1;
    }

    if(interval > maxTime){
        puts("Interval cannot be larger than time!");
        return 1;
    }

    /* finish arg handling, begin execution */

    printf("Input file is:%s, Output file is:%s\n", inFileName, outFileName);

    // TODO: replace with fflib's read in img if it works
    inFile = fopen(inFileName, "rb");
    if (!inFile){
        fprintf(stderr, "Couldn't open %s. Sorry.\n", inFileName);
        return 1;
    }

    buffer = malloc(READIN_BUFFER*sizeof(char));
    bytes=fread(buffer, 1, READIN_BUFFER*sizeof(char), inFile);
    fprintf(stdout,"Read in %u bytes.\n", (unsigned int) bytes);
    // end TODO

    // test of struct (just assign pointer, don't need to copy memory)
    
    workingImage.fsize=bytes;    
    workingImage.imgPtr=buffer;
    workingImage.outFileName=outFileName;

    dumpImgAtIntervals(workingImage, interval, maxTime);
    free(buffer);
    fclose(inFile);
    return 0;
}
*/
/** END IMG SRC FOR MERGE **/

int main(int argc, char** argv){
    char *logo="   ________          __\n  / _/ _/ /____ ___ / /_\n / _/ _/ __/ -_|_-</ __/\n/_//_/ \\__/\\__/___/\\__/\n";
    char *banner=" FFTEST: Fun Function Tests. Flood thy RAM for fun! \n=====================================================\n\
 Usage: fftest [options]\n\
 -n Use biNary mode for reading and writing.\n\
 -r <filename> Read in previously-generated logartithm file\n\
 -w <filename> Generate logarithms and write to file\n\
 -g Generate logarithms without a file. Hold them in memory until user prompts.\n\
 -b <upper bound> Specify a positive integer for the amount of logs to be generated. Logs are generated from ln(1) to ln(b).\n\
 Default behaviour: If invoked with no options -g is assumed. If -b is unspecified a vast number is assumed (200mil).";

    int upperBound=0;
    int binaryMode = 0;

    /* handle getopts */
    opterr=1;
    int thisArg;
    int mode=0;
    char *fileName = NULL;
    float *logTable = NULL;

    while ((thisArg=getopt(argc, argv, "hr:w:gb:n")) != -1){
        switch(thisArg){
            case'r':
                fileName=optarg;
                printf("Reading log file %s...\n", fileName);
                mode=READ_IN; 
                break;
            case'w':
                fileName=optarg;
                printf("Logs will be written to log file %s...\n", fileName);
                mode=WRITE_OUT;
                break;
            case'g':
                puts("Call to generate only. No logfile will be used.");
                mode=GENERATE_ONLY;
                break;
            case'b':
                upperBound=atoi(optarg);
                break;
            case'n':
                binaryMode=1;
                break;
            // print help banner in these cases
            case'h':
                printf("%s\n%s\n",logo, banner);
                exit(0);
            case'?':
                printf("%s\n", banner);
                exit(1);
            default:
                abort(); break;
        }
    }
    
    if (mode==0){
        puts("Mode unset; assuming generate only.");
        mode=GENERATE_ONLY;
    }

    if (binaryMode){
        puts("Reading and writing files in binary mode.");
    } else {
        puts("Reading and writing files in text mode. Note: This is slow and likely to consume much space.");
        puts("Consider using binary mode and the conversion & comparison utility for analysis.");
    }

    /* getopts complete, carry on */
    
    // This should handle unset and bad input to -b
    if (upperBound<=0&&(mode!=READ_IN)){
        printf("Total logs to generate is unset. Using default value of %d.\n", DEFAULT_BOUND);
        upperBound=DEFAULT_BOUND;
    }
    
    // Now do the work based on which was selected.
    switch (mode) {
        case READ_IN:
           if (binaryMode) {
               readInBin(fileName, &logTable, &upperBound);
           } else {
               readInTxt(fileName, &logTable, &upperBound);
           }
           #ifdef DEBUG
           printf("UpperBound was: %d\n", upperBound);
           #endif
           printLogTableToCon(logTable, upperBound);
           idle("");
           break;
        case WRITE_OUT:
           logTable = allocateLogTable(upperBound);
           generateLogs(logTable, upperBound);

           if (binaryMode){
               writeOutBin(fileName, logTable, upperBound);
           } else {
               writeOutTxt(fileName, logTable, upperBound);
           }

           break;
        case GENERATE_ONLY:
           logTable = allocateLogTable(upperBound);
           generateLogs(logTable, upperBound);
           generateLogsOnly(logTable, upperBound);
           break;
    }

    free(logTable); // may need to handle sigterm to ensure this is freed
    return 0;
}

int idle(char* msg){
    puts("Currently holding the logarithm table in memory.");
    printf("%sCrtl+c or ENTER to quit.\n", msg);

    getchar();
    return 0;
}

float *allocateLogTable(int upperBound){
    // pointer to allocate array in heap memory
    float *logTable = malloc(upperBound* sizeof(float));
#ifdef DEBUG
    if (logTable){
        printf("Allocated float array with %d length.\n", upperBound);
    }
#endif
    return logTable;
}

int generateLogsOnly(float *logTable, int upperBound){
    printLogTableToCon(logTable, upperBound);

    printf("generation of %d logs complete... ", upperBound);
    idle("");
    return 0;
}

int printLogTable(float *logTable, int upperBound){
    // print result TODO: better format; this goes well beyond 80cols
    for(int i=0; i<upperBound; i++){
        if (i%10==0&&i!=0) puts(""); 
        printf("ln(%d): %2.4f\t", i+1, logTable[i]);
    }
    puts("");
    return 0;
}

int printLogTableToCon(float *logTable, int upperBound){
    if (upperBound > PRINT_BOUND_LIMIT){
        printLogTable(logTable, PRINT_BOUND_LIMIT);
        puts("Large number of logs, printed only a subset!");
    } else {
        printLogTable(logTable, upperBound); 
    }
    return 0;
}

int generateLogs(float *logTable, int upperBound){
    for(int i=1; i<=upperBound; i++){
        // ln(0) is -inf... we don't want that
        logTable[i-1]=log(i*1.0);
    }
    return 0;
}
