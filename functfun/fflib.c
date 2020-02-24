/*Funfunct common functions library*/
/*Authored: 22/01/2020 */
/*Author: MJB */
#include<stdio.h> // file and console IO
#include<stdlib.h> // malloc etc
#include<unistd.h> // for sleep()
#include<string.h> // for strcat, strtok etc
#include"fflib.h"

// non-public function
char *generateImgFileName(const char *fileName, int fileNumber);

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
    
    #ifdef DEBUG
    if (logTable){
        puts("Logtable Allocation Successful. Beginning ReadIn...");
    } else {
        fprintf(stderr, "Problem encountered allocating log table.\n");
    }
    #endif
    // read in table
    fread((*logTable), sizeof(float), *upperBound, binFile);
    if(ferror(binFile)){
        fprintf(stderr, "Problem encountered reading in log table.\n");
    }

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

    #ifdef DEBUG
    if (*logTable){
        puts("Logtable Allocation Successful. Beginning ReadIn...");
    }
    #endif 

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

// read in image file to buffer (edits arg in pointer)
size_t readInImg(const char *fileName, char **buffer){
    size_t bytes;
    FILE *imgFile=fopen(fileName, "rb");

    if (!imgFile){
        fprintf(stderr, "Couldn't open %s for reading. Sorry.\n", fileName);
        return 1;
    }

    buffer = malloc(READIN_BUFFER*sizeof(char));
    bytes=fread(buffer, 1, READIN_BUFFER*sizeof(char), imgFile);
    fprintf(stdout,"Read in %u bytes.\n", (unsigned int) bytes);

    fclose(imgFile);
    return bytes;
}

int dumpImgAtIntervals(imgFile workingImage, int interval, int maxTime){
   int fileNumber=1;
   char *outFileName;
   for (int i=0; i<maxTime; i+=interval){
        outFileName=generateImgFileName(workingImage.outFileName, fileNumber);
        dumpImgToFile(workingImage, outFileName);
        sleep(interval);
        fileNumber++;
    }
    free(outFileName);
}

int dumpImgToFile(imgFile workingImage, const char *fileName){
    size_t outBytes;
    FILE *outFile=fopen(fileName, "wb");
    if (!outFile){
        fprintf(stderr, "%s couldn't be opened for writing.\n", fileName);
        return 1;
    }
    outBytes=fwrite(workingImage.imgPtr, 1, workingImage.fsize*sizeof(char), outFile); 
    fprintf(stdout,"Wrote out %u bytes to %s.\n", (unsigned int) outBytes, fileName);
    fclose(outFile);
    return 0;
}

char *generateImgFileName(const char *fileName, int fileNumber){
    char *fileNameBuf=malloc(sizeof(char)*FILEBUFSIZE); // freed in calling function
    char fileNameWrk[FILEBUFSIZE];
    char *token;
    
    // strtok modifies the filename string so we'll copy it to a buffer
    strcpy(fileNameWrk, fileName);

    // imagine this section in Java or C++
    token = strtok(fileNameWrk, ".");
    sprintf(fileNameBuf, "%s%d.", token, fileNumber);
    token = strtok(NULL, ".");
    strcat(fileNameBuf, token);

    // check that filename was valid
    token = strtok(NULL, ".");
    if (token != NULL){
        fprintf(stderr, "Possible malformation in filename %s. Please ensure there is only one period for the file extension.\n", fileName);
    }

    #ifdef DEBUG
    printf("Generated filename from:%s to:%s\n", fileName, fileNameBuf);
    #endif

    return fileNameBuf;
}
