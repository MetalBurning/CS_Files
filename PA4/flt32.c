#include "field.h"
#include "flt32.h"
#include <stdio.h>
/** @file flt32.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in flt32.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Jacob Rede</b> goes here
 */
/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_sign (flt32 x) { 
	int k = x >> 31;
	    if (k & 1) {
	 		return 1;
	    }
	return 0;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_exp (flt32 x) {
	return getField(x,30,23,0);
  //return 0; /* implement this */
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_get_val (flt32 x) {
   int value = getField(x,22,0,0);
   value |= 1 << 23;
   return value;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
void flt32_get_all(flt32 x, int* sign, int*exp, int* val) {
	*sign = flt32_get_sign(x);
	*exp = flt32_get_exp(x);
	*val = flt32_get_val(x);
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
int flt32_left_most_1 (int value) {
	for (int c = 31; c >= 0; c--) {
		if (getBit(value, c) == 1) {
			return c;
		}
	}
  return -1;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_abs (flt32 x) {
	if (flt32_get_sign(x)) {
		 x &= ~(1 << 31);
	}
  return x;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_negate (flt32 x) {
	if (flt32_get_sign(x)) {
		 return x &= ~(1 << 31);
	}
  return x |= 1 << 31;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_add (flt32 x, flt32 y) {
	int xExponent = flt32_get_exp(x);
	int yExponent = flt32_get_exp(y);
	int yMantissa = flt32_get_val(y);
	int xMantissa = flt32_get_val(x);
	
	if (x == 0) {//x = 0.0
		return y;
	} else if (y == 0) {//y = 0.0
		return x;
	}
	// printf("\nBinary x: ");
	// 	for (int c = 31; c >= 0; c--) {
	// 		if (getBit(x, c)) {
	// 			printf("1");
	// 		} else {
	// 			printf("0");
	// 		}
	// 		if (c == 31 || c ==23) {
	// 			printf("-");
	// 		}
	// 	}
	
	if (xExponent > yExponent) {
		int shiftNeeded = xExponent - yExponent;
		yMantissa = yMantissa >> shiftNeeded;
		yExponent = yExponent+shiftNeeded;
	} else {
		int shiftNeeded = yExponent - xExponent;
		xMantissa = xMantissa >> shiftNeeded;
		xExponent = xExponent+shiftNeeded;
	}

	if (flt32_get_sign(y)== 1) {
		yMantissa = ~(yMantissa)+1;//##################3negative negate
	}
	if (flt32_get_sign(x)== 1) {
		xMantissa = ~(xMantissa)+1;//##################3negative negate
	}
	//addition
		int newMantissa = 0x00000000;
		int carryBit = 0;
		for(int j = 0; j <  32; j++) {
			if (getBit(yMantissa, j) && getBit(xMantissa, j)) {//if both y and x are 1 then newMantissa = 0
				if (carryBit) {//if carry bit from last location and both are set, then we set to 1 
					newMantissa = setBit(newMantissa, j);
					carryBit = 1;
				} else {
					newMantissa = clearBit(newMantissa, j);
					carryBit = 1;
				}
			} else if (getBit(yMantissa, j) && (getBit(xMantissa, j) == 0)) {//then y is 1 and x is 0 newMantissa = 1
				if (carryBit) {
					newMantissa = clearBit(newMantissa, j);
					carryBit = 1;
				} else {
					newMantissa = setBit(newMantissa, j);
					carryBit = 0;
				}
			} else if ((getBit(yMantissa, j) == 0) && getBit(xMantissa, j)) {//if y = 0 and x = 1 newMantissa = 1
				if (carryBit) {
					newMantissa = clearBit(newMantissa, j);
					carryBit = 1;
				} else {
					newMantissa = setBit(newMantissa, j);
					carryBit = 0;
				}
			} else {//####################################################### both are set to 0 newMantissa = 1
				if (carryBit) {
					newMantissa = setBit(newMantissa, j);
				} else {
					newMantissa = clearBit(newMantissa, j);
				}
				carryBit = 0;
			}
		}
		//end addition
		int newSign = 0;
		if (flt32_get_sign(newMantissa) == 1) {
			newMantissa = ~(newMantissa)+1;
			newSign = 1;
		}
		int leftBitLocation = flt32_left_most_1(newMantissa);
		if (leftBitLocation > 23) {
			printf("\nrightshift %d\n", leftBitLocation);
			int normailizeShift = leftBitLocation - 23;
			newMantissa = newMantissa >> normailizeShift;
			xExponent = xExponent + normailizeShift;
		} else if (leftBitLocation < 23 && leftBitLocation >= 0) {
			printf("\nleftshift %d\n", leftBitLocation);
			int normailizeShift = 23 - leftBitLocation;
			newMantissa = newMantissa << normailizeShift;
			xExponent = xExponent - normailizeShift;
		} else if (leftBitLocation == 23) {
			 int normailizeShift = 23 - leftBitLocation;
			// newMantissa = newMantissa << normailizeShift;
			// xExponent = xExponent - normailizeShift;
		} else {
			printf("\n%d\n", leftBitLocation);
			int normailizeShift = 30;
			newMantissa = newMantissa << normailizeShift;
			xExponent = xExponent - normailizeShift;
		}
		//remove implicit 1
	int totalValue = setField(getField(newMantissa,22,0,0),30,23,xExponent);//30-23 for the 8 bit exponenet (31 for the sign)
	printf("\nBinary x: ");
	for (int c = 31; c >= 0; c--) {
		if (getBit(totalValue, c)) {
			printf("1");
		} else {
			printf("0");
		}
		if (c == 31 || c ==23) {
			printf("-");
		}
	}
	if (newSign) {
		totalValue = setBit(totalValue, 31);
	} else {
		totalValue = clearBit(totalValue, 31);
	}
	
	return totalValue;
}

/** @todo Implement in flt32.c based on documentation contained in flt32.h */
flt32 flt32_sub (flt32 x, flt32 y) {
	if (y > 0) {
		y = setBit(y,31);
	} else {
		y = clearBit(y,31);
	}
  return flt32_add(x, y);
}

