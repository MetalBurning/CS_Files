// PA2 Assignment - convert.h
// Author: Jacob Rede
// Date:   9/4/2014
// Class:  CS270
// Email:  jare1987@rams.colostate.edu
#include <string.h>
#include <math.h>
#include <stdio.h>
// char2int
// Converts from a character to an integer digit
// if character '0'..'9' convert to 0..9
// else if character 'A'..'F' convert to 10..15
// else convert to -1
int char2int(char digit) {
	int result = digit - '0';
	if (result > 9) {//must be letter
		result = result - 7;//offset
		if (result > 15) {//hex only goes upto 15 (F)
			return -1;
		}
	}
	return result;
}
 
// int2char
// Converts from an integer digit to a character
// if integer 0..9 convert to '0'..'9'
// else if integer 10..15 convert to 'A'..'F'
// else convert to 'X'
char int2char(int digit) {
	if (digit < 10) {
		return (char) (((int)'0')+digit);
	} else {
		switch(digit) {
			case 10 :
				return 'A';
				break;
			case 11 :
				return 'B';
				break;
			case 12 :
				return 'C';
				break;
			case 13 :
				return 'D';
				break;
			case 14 :
				return 'E';
				break;
			case 15 :
				return 'F';
				break;
			default :
				return 'X';
		}
	}
}
 
// Convert integer to string in specified base and print
// 2 <= base <= 16
void int2ascii(int value, int base) {
	if (value == 0) {
		return;
	}
	int baseDivision = value / base;
	int module = value % base;
	int2ascii(baseDivision, base);
	printf("%c", int2char(module));
}

// Convert string in specified base to integer and print
// 2 <= base <= 16
void ascii2int(char *ascii, int base) {
	int convert = 0;
    for (int i = 0; i < strlen(ascii); i++) {
        // Extract a character
        char c = ascii[i];
        // Run the character through char2int
        int digit = char2int(c);
        int powerBase = base;
        for(int j = 1; j < strlen(ascii)-(i+1);j++) {//calc power
            powerBase = (powerBase*base);
        }
        //printf("powerBase: %d \n",powerBase);
        if ((strlen(ascii)-1) == i) {
			convert += digit;//if last number dont multiple power
        } else {
        	convert += digit * powerBase;
        }
    }
   printf("%d", convert);
}
