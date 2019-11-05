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

// mode definitions
#define READ_IN 1
#define WRITE_OUT 2
#define GENERATE_ONLY 3

int readInLogFile(char *fileName, float *logTable, int upperBound);
int writeOutLogFile(char *fileName, float* logTable, int upperBound);
int generateLogsOnly(float *logTable, int upperBound);

int main(int argc, char** argv){
    char *logo="   ________          __\n  / _/ _/ /____ ___ / /_\n / _/ _/ __/ -_|_-</ __/\n/_//_/ \\__/\\__/___/\\__/\n";
    char *banner=" FFTEST: Fun Function Tests. Flood your RAM for fun! \n=====================================================\n\
 Usage: ... Note: Only the first arg of ... is honoured. -b is optional.";

    int upperBound=0;

    /* handle getopts */
    opterr=1;
    int thisArg;
    int mode=0;
    char *fileName = NULL;

    if(argc>3){
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
        puts("Mode unset, assuming generate only.");
        mode=GENERATE_ONLY;
    }

    /* getopts complete, carry on */
    
    // This should handle unset and bad input to -b
    if (upperBound==0){
        printf("Total logs to generate is unset. Using default value of %d.\n", DEFAULT_BOUND);
        upperBound=DEFAULT_BOUND;
    }
    
    // pointer to allocate array in heap memory
    float *logTable = malloc(upperBound* sizeof(float));

    // Now do the work based on what was selected.
    switch (mode) {
        case READ_IN:
           readInLogFile(fileName, logTable, upperBound);
           break;
        case WRITE_OUT:
           writeOutLogFile(fileName, logTable, upperBound);
           break;
        case GENERATE_ONLY:
           generateLogsOnly(logTable, upperBound);
           break;
    }

    free(logTable); // may need to handle sigterm to ensure this is freed

    return 0;
}

int generateLogsOnly(float *logTable, int upperBound){
    generateLogs(logTable, upperBound);
    printLogTableToCon(logTable, upperBound);

    printf("generation of %d logs complete... ctrl+c or ENTER to quit.\n", upperBound);
    getchar();
    return 0;
}

int readInLogFile(char *fileName, float *logTable, int upperBound){
    puts("not yet ready sorry sir");
    return 0;
}

int writeOutLogFile(char *fileName, float* logTable, int upperBound){
    puts("also not yet ready, sorry again");
    return 0;
}

int printLogTable(float *logTable, int upperBound){
    // print result TODO: better format; this goes well beyond 80cols
    for(int i=0; i<upperBound; i++){
        printf("ln(%d): %3.4f\t", i, logTable[i]);
        if (i%10==0) puts(""); //newline
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
    for(int i=0; i<upperBound; i++){
        logTable[i]=log(i*1.0);
    }
    return 0;
}
