/*
 * Function headers for ffgen.c (previously fftest.c)
 * MJB 25 02 2020 
 */
#define DEFAULT_BOUND 200000000
#define PRINT_BOUND_LIMIT 500

int readLogTable(FILE *logFile);
int writeLogTable(FILE *logFile);
int generateLogs(float *logTable, int upperBound);
int printLogTable(float *logTable, int upperBound);
int printLogTableToCon(float *logTable, int upperBound);

int idle(char *msg);
int generateLogsOnly(float *logTable, int upperBound);
float *allocateLogTable(int upperBound);
