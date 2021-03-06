/** @file       logic.h
 *  @brief      ... fill this in
 *  @details    ... fill this in
 *
 *  @author     ... fill this in
 *  @date       ... fill this in
 */
 
// Include files
#include <assert.h>
#include <stdio.h>

// Enumerated type for a single bit.
typedef enum { FALSE=0, TRUE=1 } BIT;

// Function Declarations (gates)
BIT not_gate(BIT A);
BIT or_gate(BIT A, BIT B);
BIT and_gate(BIT A, BIT B);
BIT xor_gate(BIT A, BIT B);

// Function Declarations (circuits)
BIT rs_latch(BIT S, BIT R);
BIT d_latch(BIT D, BIT WE);
int adder(int O1, int O2,  BIT carryIn, BIT *carryOut);
BIT multiplexer(BIT A, BIT B, BIT C, BIT D, BIT S1, BIT S0);
void decoder(BIT A, BIT B, BIT *O0, BIT *O1, BIT *O2, BIT *O3);
