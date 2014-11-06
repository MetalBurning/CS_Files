// PA1 Assignment
// Author: Jacob Rede
// Date:   8/27/2014
// Class:  CS270
// Email:  jare1987@rams.colostate.edu

// Include files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double computeCircle(double radius)
{
    return (3.14159 * radius * radius);
}
double computeTriangle(double side)
{
	double height = (side+side+side)/2;
    return sqrt(height*(height-side)*(height-side)*(height-side));
}
double computeSquare(double value)
{
    return (value * value);
}
double computePentagon(double value)
{
	return (0.25* sqrt(5 * (5 + 2 * sqrt(5)))*(value * value));
}
double computeHexagon(double value)
{
    return (((3 * sqrt(3))/2) * (value*value) );
}
int main(int argc, char *argv[])
{
	//##############################################################arguments check
	if ((argc < 1) || (argc > 6)) {
		fprintf(stderr,"error: To many / few arguments: %s\n", argv[0]); 
		return 1;
	}
	double d[5];
	for (int i=1; i<argc; i++) {
		d[i] = atof(argv[i]);
	}
	printf("CIRCLE, radius = %0.5f, area = %0.5f.\n", d[1], computeCircle(d[1]));
	printf("TRIANGLE, length = %0.5f, area = %0.5f.\n", d[2], computeTriangle(d[2]));
	printf("SQUARE, length = %0.5f, area = %0.5f.\n", d[3], computeSquare(d[3]));
	printf("PENTAGON, length = %0.5f, area = %0.5f.\n", d[4], computePentagon(d[4]));
	printf("HEXAGON, length = %0.5f, area = %0.5f.\n", d[5],  computeHexagon(d[5]));
    return 0;
}