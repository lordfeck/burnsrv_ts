/*Funfunct common functions library*/
/*Authored: 22/01/2020 */
/*Author: MJB */
#include<stdio.h>
#include<stdlib.h>

#include"ffglobals.h"
#include"fflib.h"

int readInBin(const char *fileName, float **logTable, int *upperBound){
    FILE *binFile=fopen(fileName, "rb");
    
    // read size in integer then allocate log table
    fread(upperBound, sizeof(int), 1, binFile);
    #ifdef DEBUG
    printf("Upper Bound Read: %d\n", *upperBound);
    #endif
    *logTable=malloc(*upperBound * sizeof(float));
    
    if (logTable){
        puts("Logtable Allocation Successful. Beginning ReadIn...");
    }

    // read in table
    fread((*logTable), sizeof(float), *upperBound, binFile);

    fclose(binFile);
    return 0;
}

int writeOutBin(const char *fileName, const float *logTable, int upperBound){
    // open file for writing in bin, overwrite if existing
    FILE *binFile=fopen(fileName, "wb");
    
    // write size in integer (remember to read this as first element)
    fwrite(&upperBound, sizeof(int), 1, binFile);
    // write table
    fwrite(logTable, sizeof(float), upperBound, binFile);

    puts("These warnings may be incorrect. Please disregard for now.");
    if(feof(binFile)){
        printf("Write out to %s complete. Wrote %d logs.\n", fileName, upperBound);
    } else {
        printf("Problem writing to %s! Data may be corrupted.", fileName);
    }

    fclose(binFile);
    return 0;
}

