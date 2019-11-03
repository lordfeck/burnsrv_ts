/*****************************************************************************/
/* CSC3002 APPROXIMEM MJB 03/11/2019 */
/* Funct Fun Test */
/* Generate a large log table: */
/* Dump it in a text file or put it in RAM as you desire.*/
/* Uses the mature, stabler Cmath library.*/
/*****************************************************************************/
#include<stdio.h>
#include<math.h>
#include<getopt.h>

int main(int argc, char** argv){
    // Initially assume 2G to be filled, later have getopts
    // but while we test let's just keep that low 

    // 16MB
    int maxBound=2*8*100000;
    // pointer to allocate array in heap memory
    double **logTable;
    
    // initial test, del later
    double notManyLogs[100];
    for(int i=0; i<100; i++){
        notManyLogs[i]=log(i*1.0);
    }

    // print result todo: better format
    for(int i=0; i<=100; i++){
        printf("ln(%d): %3.4f\t", i, notManyLogs[i]);
        if (i%10==0) puts("");
    }
    puts("");

    return 0;
}
