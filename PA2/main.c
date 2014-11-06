// PA2 Assignment - main.c
// Author: Jacob Rede
// Date:   9/4/2014
// Class:  CS270
// Email:  jare1987@rams.colostate.edu

#include <stdio.h>
#include "convert.h"
#include <string.h>
#include <math.h>
// Test Program
int main(int argc, char *argv[]) {
    char test = '0';
   // int resultTest = char2int(test);
    printf("resultTest = %d \n", char2int(test));

    int testitn = 0;
   // int resultTest = char2int(test);
    printf("resultTest = %c \n", int2char(testitn));
        // int base = 6;
        // int powerBase = base;
        // for(int j = 0; j < 3;j++) {
        //     powerBase = (powerBase*base);//produces 6^4
        // }
        // printf("%d",powerBase);
    //Base 16 (hexadecimal)
    int value = 1234;
    printf("%d (base 10) = ", value); int2ascii(value, 16); printf(" (base 16)\n");
    char *string = "162E";
    printf("%s (base 16) = ", string); ascii2int(string, 16);  printf(" (base 10)\n");

     // Base 8 (octal)
    value = 1234;
    printf("%d (base 10) = ", value); int2ascii(value, 8); printf(" (base 8)\n");
    string = "4567";
    printf("%s (base 8) = ", string); ascii2int(string, 8);  printf(" (base 10)\n");

    // Base 2 (binary)
    value = 1234;
    printf("%d (base 10) = ", value); int2ascii(value, 2); printf(" (base 2)\n");
    string = "10011011";
    printf("%s (base 2) = ", string); ascii2int(string, 2);  printf(" (base 10)\n");

    // Base 6 (unusual!)
    value = 1234;
    printf("%d (base 10) = ", value); int2ascii(value, 6); printf(" (base 6)\n");
    string = "4532";
   printf("%s (base 6) = ", string); ascii2int(string, 6);  printf(" (base 10)\n");
}