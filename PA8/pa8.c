#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDigit(unsigned short digit) {
	char character = (char)(((int)'0')+digit);
	printf("%c\n", character);
}
void printValue(unsigned short value) {
	if(value < 10) {
		printDigit(value);
	} else {
		printValue(value / 10);
		printDigit(value % 10);
	}
}
int main(int argc, char *argv[]) {
	
	// if(argc > 0) {
	// 	userInput = atof(argv[1]);
	// } else {
		int input;
		printf("Please input an integer value: ");
    	scanf("%d", &input);
    	if (input > 32767 || input < 0) {
    		printf("Number out of range\n");
			return -1;
    	} 
		unsigned short userInput = input;
	//}
	//printf("%d",userInput);
	if (userInput > 32767 || userInput < 0) {
		printf("Number out of range\n");
		return -1;
	}
	printValue(userInput);
	return 0;
}