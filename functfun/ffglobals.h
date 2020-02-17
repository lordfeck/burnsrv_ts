/* Global header for typedefs */
#ifndef FFGLOBALS_H
#define FFGLOBALS_H

/* Pack it in a struct, this MIGHT make it easier */
typedef struct imgFile {
    size_t fsize;
    char *outFileName;
    // here char is used to store a byte, NOT a string!
    char *imgPtr;
} imgFile;

// fftest.c
#define FFTEST_HEADER_V1 "|FFTEST_LOGARITHMS|FORMAT_V1|upperBound:%d|\n"
#define FLOAT_FORMAT "%4.20f\n"
#define STR_BUFFER_SIZE 30

// fftest.c mode definitions - do NOT change!
#define READ_IN 1
#define WRITE_OUT 2
#define GENERATE_ONLY 3

#define FFIMG_JPG "ffout.jpg"

// Buffer for reading in images in bytes (20MB)
#define READIN_BUFFER 20000000

#endif
