/*cmath for simpletons*/
#include"mathops.h"
//ifdef debug include stdio (or use a debug macro header)
//#include<stdio.h>
//endif
#ifndef MATHOPS_H
#define MATHOPS_H

// only supports positive exponents
int simple_exp(int *base, int *exponent){
    int result=1;
    for(int i=0; i<*exponent; i++) {
        result *= *base;
    }
//#ifdef DEBUG
//    fprintf(stderr, "Value of base %d exponent %d result %d", *base, *exponent, result);
//#endif
    return result;
}

// for doubles
double simple_expd(int *base, int *exponent){
    double result=1.0;
    for(int i=0; i<*exponent; i++) {
        result *= 1.0**base;
    }
    return result;
}
// Calculate euler's number to a degree of accuracy.
double euler(){
    return 0.0;
}

// returns e^x to a degree of accuracy using a Taylor series
double e(int *base){
    double result=1.0;
    for (int i=1; i<MAX_RANGE; i++){
        result += (simple_expd(base, &i) / factd(&i));
    }
    return result;
}

// factorial for integers
int fact(int *x){
    int result=1;
    for (int i=*x; i>0; i--){
        result *=i;
    }
    return result;
}


// factorial for doubles
double factd(int *x){
    double result=1.0;
    for (int i=*x; i>0; i--){
        result *= 1.0*i;
    }
    return result;
}

#endif
