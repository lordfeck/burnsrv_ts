/* Interface to fflib.c */
/* Authored 22/01/2020 */
/* Author: MJB */

// Binary Mode Functions
int readInBin(const char *fileName, float **logTable, int *upperBound);
int writeOutBin(const char *fileName, const float* logTable, int upperBound);

