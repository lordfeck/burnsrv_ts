// MathOps for Approximate Memories
// MathOps should be accurate and not approximate...
// at least untill we put these in memory

#define MAX_RANGE 30 // Max range of 100 has underflow

/*todo: convert these to call-by-value. Simpler, wider application */
int simple_exp(int *base, int *exponent);
double e(int *base);
double euler();
double logTaylor(double *base);
double logNatural(double *base);
int fact(int *x);
double simple_expd(int *base, int *exponent);
double simple_dexpd(double *base, int *exponent);
double factd(int *x);
