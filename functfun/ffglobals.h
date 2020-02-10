/* global header for typedefs */
typedef unsigned long int absoluteUint; 

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
