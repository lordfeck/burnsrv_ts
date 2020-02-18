/*
 * Function headers for ffcmp.c
 * Authored: 21/01/2020 MJB
 */

float calculateErrorFraction(int baseDiff, int upperBound);
int calculateBaseDiff(float *logTable1, float *logTable2, int upperBound);
int returnLowerBound(int upperBound1, int upperBound2);
int compareFloats(int fcount, int argc, char** argv);

#define FLOAT_MODE 1
#define BYTE_MODE 2
