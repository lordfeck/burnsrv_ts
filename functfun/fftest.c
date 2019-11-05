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
#include<getopt.h>

#include"fftest.h"

#define DEFAULT_BOUND 200000000
#define PRINT_BOUND_LIMIT 10000

int readLogTable(FILE *logFile);
int writeLogTable(FILE *logFile);
int generateLogs(float *logTable, int upperBound);
int printLogTable(float *logTable, int upperBound);
int printLogTableToCon(float *logTable, int upperBound);

int main(int argc, char** argv){
    // Initially assume 2G to be filled, later have getopts
    // but while we test let's just keep that low 

    absoluteUint maxBound=4*8*100000; // what do you

    int upperBound=DEFAULT_BOUND;
    // pointer to allocate array in heap memory
    float *logTable = malloc(upperBound* sizeof(float));
    generateLogs(logTable, upperBound);
    printLogTableToCon(logTable, upperBound);

    printf("generation of %d logs complete... ctrl+c or ENTER to quit.\n", upperBound);
    getchar();

    free(logTable); // may need to handle sigterm to ensure this is freed

    return 0;
}

int printLogTable(float *logTable, int upperBound){
    // print result TODO: better format
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
