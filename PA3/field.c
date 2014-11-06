#include "field.h"
#include <stdio.h>
#include <stdint.h>
/** @file field.c
 *  @brief You will modify this file and implement six functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. For example, methods you write may need a mask value.
 *  You might write a method to compute mask for you and use it wherever
 *  it is needed as oposed to just puting the code in line.
 * <p>
 * @author <b>Your name</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	for (int c = 31; c >= 0; c--) {
    	int k = value >> c;
	    if (k & 1) {
	    	if (c == position) 
	 			return 1;
	    }
	}
	return 0;
}
/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	return value |= 1 << position;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
    return value &= ~(1 << position);
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, int isSigned) {
	if (!isSigned) {
		if (hi < lo) {
			int temp = hi;
			hi = lo;
			lo = temp;
		}
		int leftShift = (31-hi);
		int rightShift = (lo+leftShift);
		int numBits = (hi - lo);
		value = value << leftShift;
		value = value >> rightShift;
		//clear bits from right shift
		for (int j = 0; j < 32; j++) {
			if (j > numBits) {
				value &= ~(1 << j);
			}
		}
		return value;
	} else {
		if (hi < lo) {
			int temp = hi;
			hi = lo;
			lo = temp;
		}
		int leftShift = (31-hi);
		int rightShift = (lo+leftShift);
		value = value << leftShift;
		value = value >> rightShift;
		return value;
	}
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setField (int oldValue, int hi, int lo, int newValue) {
	if (hi < lo) {
		int temp = hi;
		hi = lo;
		lo = temp;
	}
	
	int numBits = (hi - lo);
	int loCounter = lo;
	int counter = 0;
	while (hi >= loCounter) {//make sure were within the desired bit area
		if (numBits >= counter) {//make sure to only grab the right amount of bits from newvalue
			if (getBit(newValue, counter) == 1) {
				oldValue = setBit(oldValue, loCounter);
			} else {
				oldValue = clearBit(oldValue, loCounter);
			}
		}
		loCounter++;
		counter++;
	}
    return oldValue;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int fieldFits (int value, int width, int isSigned) {
	if (!isSigned) {
		int counter = 0;
		for (int c = 31; c >= 0; c--) {
			if (getBit(value, c) == 0) {
				counter++;
			} else {
				break;
			}
		}
		if ((32-counter) <= width) {
			return 1;
		}
	    return 0;
	} else {
		int counter = 0;
		for (int c = 31; c >= 0; c--) {
			if (value < 0) {//if negative
				if (getBit(~value, c) == 0) {//flip bits in order to count all 0 before the first 1 (since its signed)
					counter++;
				} else {
					break;
				}
			} else {
				if (getBit(value, c) == 0) {//count all 0 before first 1
					counter++;
				} else {
					break;
				}
			}
			
		}
		if ((32-counter) < width) {
			return 1;
		}
	    return 0;
	}
}