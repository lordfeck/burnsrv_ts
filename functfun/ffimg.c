/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 06/02/2020 */
/* Funct Fun Images */
/* Uses the GD library: https://libgd.github.io/ */ 
/* GD HELP: https://libgd.github.io/manuals/2.2.5/files/preamble-txt.html */ 
/*****************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include"gd.h"

#include"ffglobals.h"
#include"fflib.h"

int main(int argc, char** argv){
    gdImagePtr im;
    char *buffer = NULL; 
    char *inFileName = NULL;
    FILE *inFile = NULL;
    FILE *outFile = NULL;
    size_t bytes, outBytes;

    if (argc <2){
        puts("Need infile.");
        return 1;
    }

    inFileName = argv[1];

    printf("Input file is:%s\n", inFileName);

    inFile = fopen(inFileName, "rb");
    outFile = fopen(FFIMG_JPG, "wb");
    if (!inFile){
        fprintf(stderr, "Couldn't open %s. Sorry.\n", inFileName);
        return 1;
    }
    // FOR NOW readin 20MB, we'll need to adjust for larger files.
    // See what 'cmp' outputs
    buffer = malloc(READIN_BUFFER*sizeof(char));
    bytes=fread(buffer, 1, READIN_BUFFER*sizeof(char), inFile);
    fprintf(stdout,"Read in %u bytes.\n", (unsigned int) bytes);

    if (!outFile){
        fprintf(stderr, "Couldn't open %s for writing. Sorry.\n", FFIMG_JPG);
        return 1;
    }
    outBytes=fwrite(buffer, 1, bytes*sizeof(char), outFile); 
    fprintf(stdout,"Wrote out %u bytes to %s.\n", (unsigned int) outBytes, FFIMG_JPG);

    free(buffer);
    fclose(inFile);
    fclose(outFile);
    return 0;
}
