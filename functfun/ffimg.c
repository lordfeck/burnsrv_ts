/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 06/02/2020 */
/* Funct Fun Images */
/*****************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#include"ffglobals.h"
#include"fflib.h"

int main(int argc, char** argv){
    char *banner="ffimg: Hold image in memory, dump at regular intervals.\n\
Usage:\n\
./ffimg <inputFileName> <outputFileName> <time (s)> <intervals>";

    char *buffer = NULL; 
    char *inFileName = NULL;
    char *outFileName = NULL;
    FILE *inFile = NULL;
    size_t bytes;

    imgFile workingImage;

    if (argc <3){
        fprintf(stderr, "%s\n", banner);
        return 1;
    }

    inFileName = argv[1];
    outFileName = argv[2];

    printf("Input file is:%s, Output file is:%s\n", inFileName, outFileName);

    inFile = fopen(inFileName, "rb");
    if (!inFile){
        fprintf(stderr, "Couldn't open %s. Sorry.\n", inFileName);
        return 1;
    }
    // FOR NOW readin 20MB, we'll need to adjust for larger files.
    // See what 'cmp' outputs
    buffer = malloc(READIN_BUFFER*sizeof(char));
    bytes=fread(buffer, 1, READIN_BUFFER*sizeof(char), inFile);
    fprintf(stdout,"Read in %u bytes.\n", (unsigned int) bytes);

    // test of struct (just assign pointer, don't need to copy memory)
    
    workingImage.fsize=bytes;    
    workingImage.imgPtr=buffer;
    workingImage.outFileName=outFileName;

    dumpImgToFile(workingImage, workingImage.outFileName);

    free(buffer);
    fclose(inFile);
    return 0;
}
