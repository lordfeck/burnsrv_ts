/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 03/11/2019 */
/* Funct Fun Test */
/* Generate a large log table: */
/* Dump it in a text file or put it in RAM as you desire.*/
/* Uses the mature, stabler Cmath library.*/
/*****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#include"ffglobals.h"
#include"fftest.h"

#define STR_BUFFER_SIZE 20

int readInLogFile(const char *fileName, float *logTable, int *upperBound);
int writeOutLogFile(const char *fileName, const float* logTable, int upperBound);
int generateLogsOnly(float *logTable, int upperBound);
float *allocateLogTable(int upperBound);

int main(int argc, char** argv){
    char *logo="   ________          __\n  / _/ _/ /____ ___ / /_\n / _/ _/ __/ -_|_-</ __/\n/_//_/ \\__/\\__/___/\\__/\n";
    char *banner=" FFTEST: Fun Function Tests. Flood your RAM for fun! \n=====================================================\n\
 Usage: fftest [options]\n\
 -r <filename> Read in previously-generated logartithm file\n\
 -w <filename> Generate logarithms and write to file\n\
 -g Generate logarithms without a file. Hold them in memory until user prompts.\n\
 -b <upper bount> Specify a positive integer for the amount of logs to be generated.\n\
 Default behaviour: If invoked with no options -g is assumed. If -b is unspecified a vast number is assumed (200mil).";

    int upperBound=0;

    /* handle getopts */
    opterr=1;
    int thisArg;
    int mode=0;
    char *fileName = NULL;
    float *logTable;

    if(argc>5){
        fprintf(stderr, "Invalid call; too many arguments!\n%s\n", banner);
        exit(1);
    }

    while ((thisArg=getopt(argc, argv, "hr:w:gb:")) != -1){
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

    /* getopts complete, carry on */
    
    // This should handle unset and bad input to -b
    if (upperBound<=0&&(mode!=READ_IN)){
        printf("Total logs to generate is unset. Using default value of %d.\n", DEFAULT_BOUND);
        upperBound=DEFAULT_BOUND;
    }
    
    // Now do the work based on which was selected.
    switch (mode) {
        case READ_IN:
           readInLogFile(fileName, logTable, &upperBound);
           printf("UpperBound was: %d\n", upperBound);
           break;
        case WRITE_OUT:
           logTable = allocateLogTable(upperBound);
           generateLogs(logTable, upperBound);
           writeOutLogFile(fileName, logTable, upperBound);
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

float *allocateLogTable(int upperBound){
    // pointer to allocate array in heap memory
    float *logTable = malloc(upperBound* sizeof(float));
    return logTable;
}

int generateLogsOnly(float *logTable, int upperBound){
    printLogTableToCon(logTable, upperBound);

    printf("generation of %d logs complete... ctrl+c or ENTER to quit.\n", upperBound);
    getchar();
    return 0;
}

// TODO: add read status by wrapper function, eg whether file could be
// opened or whether the format is wrong
int readInLogFile(const char *fileName, float *logTable, int *upperBound){
    FILE *logFile=fopen(fileName, "r");
    fscanf(logFile, FFTEST_HEADER_V1, upperBound);
    printf("File %s opened with upperBound of %d.\n", fileName,  *upperBound);

    logTable=allocateLogTable(*upperBound);
    puts("Logtable Allocation Successful. Beginning ReadIn...");

    char buffet[STR_BUFFER_SIZE];
    int bufferStatus=1, i=0; 
    //bufferStatus was used with sscanf
    while (bufferStatus != EOF && i<*upperBound){
        fgets(buffet, STR_BUFFER_SIZE, logFile);
        logTable[i]=strtof(buffet, NULL);
        printf("INDEX %d READ %4.20f\n", i, logTable[i]);
/*
        if (bufferStatus==0){
           puts("read error");
           fclose(logFile);
           return 2;
        }
        */
        i++;

    }

    fclose(logFile);
    return 0;
}

int writeOutLogFile(const char *fileName, const float *logTable, int upperBound){
    FILE *logFile=fopen(fileName, "w+");
    
    // First write the file header and upperBound. 
    fprintf(logFile, FFTEST_HEADER_V1, upperBound); 
    
    for(int i=0; i<upperBound; i++){
        fprintf(logFile, FLOAT_FORMAT, logTable[i]); // TODO: Improve formatting
    }

    fflush(logFile); // do we need this after every call to fprintf?
    printf("Write out to %s complete. Wrote %d logs.\n", fileName, upperBound);
    fclose(logFile);
    return 0;
}

int printLogTable(float *logTable, int upperBound){
    // print result TODO: better format; this goes well beyond 80cols
    for(int i=0; i<upperBound; i++){
        printf("ln(%d): %2.4f\t", i, logTable[i]);
        if (i%10==0) puts(""); //newline, also needs fixed
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
