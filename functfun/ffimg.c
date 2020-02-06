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
    size_t bytes;

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
    // FOR NOW readin 20k, we'll need to adjust for larger files.
    // cmp tells us that it wrote 20000 bytes exactly
    buffer = malloc(20000*sizeof(char));
    bytes=fread(buffer, 1, 20000*sizeof(char), inFile);
    fprintf(stdout,"Read in %u bytes.\n", (unsigned int) bytes);

    if (!outFile){
        fprintf(stderr, "Couldn't open %s for writing. Sorry.\n", FFIMG_JPG);
        return 1;
    }
    bytes=fwrite(buffer, 1, 20000*sizeof(char), outFile); 
    fprintf(stdout,"Wrote out %u bytes to %s.\n", (unsigned int) bytes, FFIMG_JPG);

    free(buffer);
    fclose(inFile);
    fclose(outFile);
    return 0;
}
