#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printDigit(unsigned short digit) {
	char character = (char)(((int)'0')+digit);
	printf("%c", character);
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
	//##############################################################arguments check
	if ((argc < 1) || (argc > 2)) {
		fprintf(stderr,"error: To many / few arguments: %s\n", argv[0]); 
		return 1;
	}
	unsigned short userInput = atof(argv[1]);
	//printf("%d",userInput);
	if (userInput > 32767 || userInput < 0) {
		printf("Number out of range\n");
		return -1;
	}
	printValue(userInput);
	return 0;
}