/*Funfunct common functions library*/
/*Authored: 22/01/2020 */
/*Author: MJB */
#include<stdio.h>
#include<stdlib.h>

#include"ffglobals.h"
#include"fflib.h"

int readInBin(const char *fileName, float **logTable, int *upperBound){
    FILE *binFile=fopen(fileName, "rb");

    #ifdef DEBUG
    if (binFile!=NULL) {
        fprintf(stderr, "File: %s successfully opened.\n", fileName);
    } else {
        fprintf(stderr, "Problem opening the file %s.\n", fileName);
    }
    #endif
   
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
    
    if(ferror(binFile)){
        printf("Problem writing to %s! Data may be corrupted.", fileName);
    } else {
        printf("Write out to %s complete. Wrote %d logs.\n", fileName, upperBound);
    }

    fflush(binFile);
    fclose(binFile);
    return 0;
}

int writeOutTxt(const char *fileName, const float *logTable, int upperBound){
    FILE *logFile=fopen(fileName, "w+");
    
    // First write the file header and upperBound. 
    fprintf(logFile, FFTEST_HEADER_V1, upperBound); 
    
    for(int i=0; i<upperBound; i++){
        fprintf(logFile, FLOAT_FORMAT, logTable[i]); 
    }
    
    if(ferror(logFile)){
        printf("Problem writing to %s! Data may be corrupted.", fileName);
    } else {
        printf("Write out to %s complete. Wrote %d logs.\n", fileName, upperBound);
    }

    fflush(logFile); 
    fclose(logFile);
    return 0;
}

int readInTxt(const char *fileName, float **logTable, int *upperBound){
    FILE *logFile=fopen(fileName, "r");
    fscanf(logFile, FFTEST_HEADER_V1, upperBound);
    #ifdef DEBUG
    printf("File %s opened with upperBound of %d.\n", fileName,  *upperBound);
    #endif

    *logTable=malloc(*upperBound * sizeof(float));
    if (*logTable){
        puts("Logtable Allocation Successful. Beginning ReadIn...");
    }
    
    char buffet[STR_BUFFER_SIZE];

    for(int i=0; i<*upperBound; i++) {
        fgets(buffet, STR_BUFFER_SIZE, logFile);
        (*logTable)[i]=(float)atof(buffet);
        #ifdef DEBUG
        printf("INDEX %d READ %4.20f\n", i, (*logTable)[i]);
        #endif
    }

    #ifdef DEBUG 
    puts("ReadIn complete. Closing file.");
    #endif
    fclose(logFile);
    return 0;
}
