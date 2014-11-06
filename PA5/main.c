/** @mainpage CS270 Fall 2014
 *  \htmlinclude "PA5.html"
 */

/** @file: main.c
 *  @brief Driver to test functions of number_detective.c (do not modify)
 *
 * @details This is a driver program ... fill this in
 * <p>
 * @author ... fill this in
 * @date   ... fill this in
 */

// Include files
#include "logic.h"

/** Entry point of the program
 * @param   argc count of arguments, will always be at least 1
 * @param   argv array of parameters to program argv[0] is the name of
 *          the program, so additional parameters will begin at index 1
 * @details If one of the test cases fail then the program will assert.
 * @return  0 the Linux convention for success.
 */
int main(int argc, char *argv[])
{
    // check NOT gate truth table
    // A   NOT(A)
    // 0     1
    // 1     0
    printf("===== Testing not_gate =====\n");
    assert(not_gate(FALSE) == TRUE); 
    assert(not_gate(TRUE) == FALSE); 


    // check OR gate truth table
    // A B (A OR B)
    // 0 0   0
    // 0 1   1
    // 1 0   1
    // 1 1   1
    printf("===== Testing or_gate =====\n");
    assert(or_gate(FALSE,FALSE) == FALSE); 
    assert(or_gate(FALSE,TRUE) == TRUE); 
    assert(or_gate(TRUE,FALSE) == TRUE); 
    assert(or_gate(TRUE,TRUE) == TRUE); 
    
    // check AND gate truth table
    // A B (A AND B)
    // 0 0   0
    // 0 1   0
    // 1 0   0
    // 1 1   1
    printf("===== Testing and_gate =====\n");
    assert(and_gate(FALSE,FALSE) == FALSE); 
    assert(and_gate(FALSE,TRUE) == FALSE); 
    assert(and_gate(TRUE,FALSE) == FALSE); 
    assert(and_gate(TRUE,TRUE) == TRUE); 

    // check XOR gate truth table
    // A B (A XOR B)
    // 0 0   0
    // 0 1   1
    // 1 0   1
    // 1 1   0
    printf("===== Testing xor_gate =====\n");
    assert(xor_gate(FALSE,FALSE) == FALSE); 
    assert(xor_gate(FALSE,TRUE) == TRUE); 
    assert(xor_gate(TRUE,FALSE) == TRUE); 
    assert(xor_gate(TRUE,TRUE) == FALSE); 
    
    // check RS latch truth table
    // the order matters so that the saved_bit will be true when expected
    //  S	      R	    saved_bit   rs_latch(S,R)
    //  FALSE	FALSE	FALSE	    will assert in rs_latch
    //  FALSE	FALSE	TRUE	    will assert in rs_latch
    //  TRUE	FALSE	FALSE	    FALSE
    //	TRUE	TRUE	FALSE	    FALSE
    //  FALSE	TRUE	FALSE	    TRUE
    //  FALSE	TRUE	TRUE	    TRUE
    //	TRUE	TRUE	TRUE	    TRUE
    //  TRUE	FALSE	TRUE	    FALSE
   
    printf("===== Testing rs_latch =====\n");
    assert( rs_latch( TRUE, FALSE )==FALSE );
    assert( rs_latch( TRUE, TRUE )==FALSE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( TRUE, TRUE )==TRUE );
    assert( rs_latch( TRUE, FALSE )==FALSE );

   // check D latch truth table
    // D WE  return
    // 0 0   previous
    // 0 1   false
    // 1 0   previous
    // 1 1   true
    printf("===== Testing d_latch =====\n");
    assert( d_latch( FALSE, TRUE )==FALSE );
    assert( d_latch( FALSE, FALSE )==FALSE );
    assert( d_latch( TRUE, TRUE )==TRUE );
    assert( d_latch( TRUE, FALSE )==TRUE );
    assert( d_latch( TRUE, FALSE )==TRUE );
    assert( d_latch( FALSE, FALSE )==TRUE );
    assert( d_latch( FALSE, TRUE )==FALSE );
    assert( d_latch( TRUE, TRUE )==TRUE );

    printf("===== Testing adder =====\n");
    BIT carryOut = 0;
    int one = 0b0101;//5   
    int two = 0b0101;//5
    assert(adder(one, two, 0, &carryOut) == 10); 
    assert(adder(one, two, 1, &carryOut) == 11); 
    one = 0b0001;//1
    two = 0b0111;//7
    assert(adder(one, two, 1, &carryOut) == 9); 
    one = 0b0111;//7
    assert(adder(one, two, 0, &carryOut) == 14); 
    one = 0b1101;//13
    two = 0b1101;//13
    assert(adder(one, two, 1, &carryOut) == 11); 
    assert(carryOut == 1);
    one = 0b1111;//15
    two = 0b1111;//15
    assert(adder(one, two, 1, &carryOut) == 15); 
    assert(carryOut == 1);
    one = 0b1111;//15
    two = 0b1111;//15
    assert(adder(one, two, 0, &carryOut) == 14); 
    assert(carryOut == 1);

    printf("===== Testing multiplexer =====\n");
    assert( multiplexer(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE)==FALSE );
    assert( multiplexer(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE)==TRUE );
    assert( multiplexer(TRUE, FALSE, TRUE, FALSE, TRUE, FALSE)==TRUE );
    assert( multiplexer(FALSE, TRUE, FALSE, TRUE, FALSE, TRUE)==TRUE );

    assert( multiplexer(FALSE, FALSE, FALSE, TRUE, TRUE, TRUE)==TRUE );
    assert( multiplexer(FALSE, FALSE, TRUE, FALSE, TRUE, FALSE)==TRUE );
    assert( multiplexer(FALSE, TRUE, FALSE, FALSE, FALSE, TRUE)==TRUE );
    assert( multiplexer(TRUE, FALSE, FALSE, FALSE, FALSE, FALSE)==TRUE );

    assert( multiplexer(TRUE, TRUE, TRUE, FALSE, TRUE, TRUE)==FALSE );
    assert( multiplexer(TRUE, TRUE, FALSE, TRUE, TRUE, FALSE)==FALSE );
    assert( multiplexer(TRUE, FALSE, TRUE, TRUE, FALSE, TRUE)==FALSE );
    assert( multiplexer(FALSE, TRUE, TRUE, TRUE, FALSE, FALSE)==FALSE );

    printf("===== Testing decoder =====\n");
    BIT O0 = FALSE;
    BIT O1 = FALSE;
    BIT O2 = FALSE;
    BIT O3 = FALSE;
    decoder(FALSE, FALSE, &O0, &O1, &O2, &O3);
    assert(O0==TRUE);
    assert(O1==FALSE);
    assert(O2==FALSE);
    assert(O3==FALSE);
    decoder(FALSE, TRUE, &O0, &O1, &O2, &O3);
    assert(O0==FALSE);
    assert(O1==TRUE);
    assert(O2==FALSE);
    assert(O3==FALSE);
    decoder(TRUE, FALSE, &O0, &O1, &O2, &O3);
    assert(O0==FALSE);
    assert(O1==FALSE);
    assert(O2==TRUE);
    assert(O3==FALSE);
    decoder(TRUE, TRUE, &O0, &O1, &O2, &O3);
    assert(O0==FALSE);
    assert(O1==FALSE);
    assert(O2==FALSE);
    assert(O3==TRUE);
    return 0;
}
