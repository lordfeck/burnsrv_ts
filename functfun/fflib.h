/* Interface to fflib.c */
/* Authored 22/01/2020 */
/* Author: MJB */

// Binary Mode Functions
int readInBin(const char *fileName, float **logTable, int *upperBound);
int writeOutBin(const char *fileName, const float* logTable, int upperBound);

// Text Mode Functions
int readInTxt(const char *fileName, float **logTable, int *upperBound);
int writeOutTxt(const char *fileName, const float* logTable, int upperBound);

// Image Utility Functions
int dumpImgAtIntervals(const char *imgPtr, const char *fileName, int interval, int maxTime);
int dumpImgToFile(const char *imgPtr, const char *fileName);
