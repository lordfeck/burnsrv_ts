#include<stdio.h>
//#define DEBUG
#include"mathops.h" 

int main(int args, int* argv)
{
    int ans;
    int base=2;
    int exponent=2;
    int toFact=6;
    int eMePls=6;
    int threeD=3;
    double dfact, dexp, weeLn;
    double lnMePls=6.0;
/*
    printf("Give me a number to square:" );
    scanf("%d", &base);

    printf("Simple exponential: %d^%d is ", base, exponent);
    ans = simple_exp(&base, &exponent);
    printf("%d.\n", ans);
    
    // test with own base
    printf("Give me a base and exponent:"); 
    scanf("%d %d", &base, &exponent);
    printf("\nSimple exponential: %d^%d is ", base, exponent);
    ans = simple_exp(&base, &exponent);
    printf("%d.\n", ans);
*/
    ans=fact(&toFact); 
    printf("Factorial of 6: %d\n", ans);

    dfact=factd(&toFact);
    dexp=simple_expd(&threeD, &threeD);

    printf("Double Factorial of 6: %2.4f\n", dfact);
    printf("Exponential Double of 3^3: %4.4f\n", dexp);

    dfact=e(&eMePls);
    printf("e^x of %d: %2.6f\n", eMePls, dfact);
    
    weeLn=0.7;
    dfact=logTaylor(&weeLn);
    printf("ln(x) of %2.6f: %2.6f\n", weeLn, dfact);

    weeLn=1.8;
    dfact=logTaylor(&weeLn);
    printf("ln(x) of %2.6f: %2.6f\n", weeLn, dfact);

    dfact=euler();
    printf("euler's number is %2.6f\n", dfact);

    dfact=logNatural(&lnMePls);
    printf("ln(x) of %f: %2.6f\n", lnMePls, dfact);

    lnMePls=0.2;
    dfact=logNatural(&lnMePls);
    puts("Test low number, then under range number:");
    printf("ln(x) of %f: %2.6f\n", lnMePls, dfact);

    lnMePls=-0.4;
    dfact=logNatural(&lnMePls);
    printf("ln(x) of %f: %2.6f\n", lnMePls, dfact);

    fprintf(stderr, "Tests complete!\n");
    return 0;
}
