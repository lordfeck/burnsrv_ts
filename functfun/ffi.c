#include<stdio.h>
/* Funct Fun Interactive */
/* Experimental idea for a 'shell' that can be accessed */

int main(int argc, char ** argv){
    float version=0.1;
    printf("FFI Prompt. v%2.4f.\n", version);
    
    printf("?");

    while ( getchar() != '\n' );
    return 0;
}
