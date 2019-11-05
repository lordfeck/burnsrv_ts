/*
 * Function headers for fftest.c
 * Note: These functions are only for fftest itself!
 * MJB 05 11 2019 
 */
#define DEFAULT_BOUND 200000000
#define PRINT_BOUND_LIMIT 10000

int readLogTable(FILE *logFile);
int writeLogTable(FILE *logFile);
int generateLogs(float *logTable, int upperBound);
int printLogTable(float *logTable, int upperBound);
int printLogTableToCon(float *logTable, int upperBound);
