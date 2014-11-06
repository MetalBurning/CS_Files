/** @file       logic.c
 *  @brief      ... fill this in
 *  @details    ... fill this in
 *
 *  @author     Jacob Rede
 *  @date       9/26/14
 */

#include "logic.h"

/**
 * Simulates NOT logic gate.
 *
 *  @param A    input to the NOT gate
 *  @return     NOT gate output, returns NOT A
 *
 * Truth table
 <pre>
        A   return
        0   1
        1   0
 </pre>
 */
BIT not_gate(BIT A)
{
    if (A==FALSE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Simulates OR logic gate.
 *
 *  @param A    first input to the OR gate
 *  @param B    second input to the OR gate
 *  @return     returns A OR B
 *
 * Truth table
 <pre>
        A B  return
        0 0    0    
        0 1    1    
        1 0    1    
        1 1    1    
 </pre>
 */
BIT or_gate(BIT A, BIT B)
{
    if (A==FALSE && B==FALSE) {
        return FALSE;
    } else {
        return TRUE;
    }
}

/**
 * Simulates AND logic gate.
 *
 *  @param A    first input to the AND gate
 *  @param B    second input to the AND gate
 *  @return     returns A AND B
 *
 * Truth table
 <pre>
        A B  return
        0 0    0    
        0 1    0    
        1 0    0    
        1 1    1    
 </pre>
 */
BIT and_gate(BIT A, BIT B)
{
    if (A==TRUE && B==TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Simulates XOR logic gate.
 *
 *  @param A    first input to the XOR gate
 *  @param B    second input to the XOR gate
 *  @return     returns A XOR B
 *
 * Truth table
 <pre>
        A B  return
        0 0    0    
        0 1    1    
        1 0    1    
        1 1    0    
 </pre>
 */
BIT xor_gate(BIT A, BIT B)
{
    if ((A==TRUE && B==FALSE) || (A==FALSE && B==TRUE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Simulates RS latch circuit.
 * Asserts if S = R = 0.
 *
 *  @param S    set input line
 *  @param R    reset input line
 *  @return     returns RS latch output
 *
 * Truth table
 <pre>
        S R  return
        0 0   assert
        0 1   1 
        1 0   0 
        1 1   previous output 
 </pre>
 */
BIT rs_latch(BIT S, BIT R)
{
    static BIT saved_bit = FALSE;
    
    // if both bits are zero then behavior of R-S latch
    // is undefined so we will have the simulation assert
    assert(!(S==FALSE && R==FALSE));
    
    // implements the truth table
    if (S==FALSE) {
        saved_bit = TRUE; // Set
    } else if (R==FALSE) {
        saved_bit = FALSE; // Reset
    } else {
        saved_bit = saved_bit; // Unchanged
    }

    return saved_bit;
}

/**
 * Simulates D latch circuit.
 * 
 *
 *  @param D    set input line
 *  @param WE   write enabled
 *  @return     returns D latch output
 *
 * Truth table
 <pre>
        D WE  return
        0 0   previous
        0 1   false
        1 0   previous
        1 1   true
 </pre>
 */
BIT d_latch(BIT D, BIT WE) {
    if (WE==TRUE && D==TRUE) {

        return rs_latch(FALSE, TRUE);

    } else if (WE==FALSE && D==TRUE) {

        return rs_latch(TRUE, TRUE);

    } else if (WE==TRUE && D==FALSE) {

        return rs_latch(TRUE, FALSE);

    } else {
        return rs_latch(TRUE, TRUE);
    }
}
/**
 * Simulates adder circuit.
 * 
 *
 *  @param O1        first number to add
 *  @param O2        second number to add
 *  @param carryIn   add to sum if set to 1
 *  @param *carryOut if result of addition is more than 4 bits set to 1
 *  @return          4 bit result of O1 + O2
 *
 */
int adder(int O1, int O2,  BIT carryIn, BIT *carryOut) {
    if (carryIn == 1) {
        if ((O1+O2+1) > 15) {
            *carryOut = 1;
            return (O1+O2+1)-16;
        } else {
            return O1+O2+1;
        }
    } else {
        if ((O1+O2) > 15) {
            *carryOut = 1;
            return (O1+O2)-16;
        } else {
            return O1+O2;
        }
    }
}
/**
 * Simulates multiplexer circuit.
 * 
 *
 *  @param A    input Bit
 *  @param B    input
 *  @param C    input
 *  @param D    input
 *  @param S1   select bit
 *  @param S0   select bit
 *  @return     A or B or C or D based on the select bits
 *
 * Truth table
 <pre>
        S1  S0  return
        0   0   A
        0   1   B
        1   0   C
        1   1   D
 </pre>
 */
BIT multiplexer(BIT A, BIT B, BIT C, BIT D, BIT S1, BIT S0) {
    if (S1==FALSE && S0==FALSE) {
        return A;
    } else if (S1==FALSE && S0==TRUE) {
        return B;
    } else if (S1==TRUE && S0==FALSE) {
        return C;
    } else {
        return D;
    }
}
/**
 * Simulates decoder circuit.
 * 
 *
 *  @param A    input 1 line
 *  @param B    input 2 line
 *  @param O0   bit to set
 *  @param O1   bit to set
 *  @param O2   bit to set
 *  @param O3   bit to set
 *
 * Truth table
 <pre>
        D WE  O0    O1      O2      O3
        0 0   1     0       0       0
        0 1   0     1       0       0
        1 0   0     0       1       0
        1 1   0     0       0       1
 </pre>
 */
void decoder(BIT A, BIT B, BIT *O0, BIT *O1, BIT *O2, BIT *O3) {
    *O0=FALSE;
    *O1=FALSE;
    *O2=FALSE;
    *O3=FALSE;
    if (A==FALSE && B==FALSE) {
        *O0=TRUE;
    } else if (A==FALSE && B==TRUE) {
        *O1=TRUE;
    } else if (A==TRUE && B==FALSE) {
        *O2=TRUE;
    } else {
        *O3=TRUE;
    }
}
