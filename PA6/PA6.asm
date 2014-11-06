; PA6 Assignment
; Author: Jacob Rede
; Date:   10/21/14
; Email:  jare1987@rams.colostate.edu
; Class:  CS270
;
; Description: Implements the manipulation of half precision (16-bit) floating point numbers

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL flt16_add      ; (option 0)
                .FILL flt16_sub      ; (option 1)
                .FILL flt16_get_sign ; (option 2)
                .FILL flt16_get_exp  ; (option 3)
                .FILL flt16_get_val  ; (option 4)
                .FILL flt16_abs      ; (option 5)
                .FILL flt16_neg      ; (option 6)
                .FILL left_most1     ; (option 7)
                .FILL left_shift     ; (option 8)
                .FILL right_shift    ; (option 9)
                .FILL binary_or      ; (option 10)

Main            LEA R0,Functions     ; get base of jump table
                LD  R1,Option        ; get option to use, no error checking
                ADD R0,R0,R1         ; add index of array
                LDR R0,R0,#0         ; get address of function
                JSRR R0              ; call selected function
                HALT

; Parameters and return values for all functions
Option          .BLKW 1              ; which function to call
Param1          .BLKW 1              ; space to specify first parameter
Param2          .BLKW 1              ; space to specify second parameter
Result          .BLKW 1              ; space to store result

; You may add variables and functions after here as you see fit. You may use JSR
; within the code of flt16_add or other functions. However, this requires that
; you save and restore return addresses, otherwise a function will not be able
; to use JSR to call another subroutine. See flt16_add for an example of how to
; save and restore a return address. When will this scheme NOT work?

; Here are some useful constants:

SIGN_MASK       .FILL x8000          ; 1 in left most bit 
EXP_MASK        .FILL x001F          ; exactly 5 bits     
VAL_MASK        .FILL x03FF          ; exactly 10 bits    
IMPL1_MASK      .FILL x0400          ; 1 in the 11 bit    
ONE             .FILL #1             ; the number 1 
TEN             .FILL #10            ; the number 10       
SIXTEEN         .FILL #16            ; the value 16


; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; Local variables, this is how you will be tested for PA6
; Do not change the names!
X               .BLKW 1              ; X parameter
Y               .BLKW 1              ; Y parameter
signX           .BLKW 1              ; sign of X
expX            .BLKW 1              ; exponent of X
valX            .BLKW 1              ; mantissa of X
signY           .BLKW 1              ; sign of Y
expY            .BLKW 1              ; exponent of Y
valY            .BLKW 1              ; mantissa of Y
signSum         .BLKW 1              ; sign of sum
expSum          .BLKW 1              ; exponent of sum
valSum          .BLKW 1              ; mantissa of sum
left1           .BLKW 1              ; location of left most 1

flt16_add_ra    .BLKW 1              ; return addess storage
;---------------------------------------temp storeage for step 2
exponent_updated	.BLKW 1
norm_shift_amount	.BLKW 1
;---------------------------------------END TEMP STORAGE FOR STEP 2
flt16_add       ST R7,flt16_add_ra   ; save return address
                LD R0,Param1         ; read X parameter
                ST R0,X              ; store X parameter
                LD R0,Param2         ; read Y parameter
                ST R0,Y              ; store Y parameter
		ST R7, flt16_add_RA	; store return address
;------STEP ONE) Extract fields from operands--------------------------------
;--------------------------------X FIRST-------------------------------------
		JSR flt16_get_sign
		LD R0, Result
		ST R0, signX		; save the sign of X
;----------------------------------------------------------------------
		JSR flt16_get_exp	; Param1 still contains X from above
		LD R0, Result
		ST R0, expX		; save the exponent of X
;----------------------------------------------------------------------
		JSR flt16_get_val
		LD R0, Result
		ST R0, valX		; save the mantissa of X
;----------------------------------------------------------------------
;--------------------------------NOW Y---------------------------------
;----------------------------------------------------------------------
		LD R1, Y		; load first param to R1
		ST R1, Param1
		JSR flt16_get_sign
		LD R0, Result
		ST R0, signY		; save the sign of X
;----------------------------------------------------------------------
		JSR flt16_get_exp	; param1 still contains Y from above
		LD R0, Result
		ST R0, expY		; save the exponent of Y
;----------------------------------------------------------------------
		LD R1, Y		; load first param to R1
		ST R1, Param1
		JSR flt16_get_val
		LD R0, Result
		ST R0, valY		; save the mantissa of X
;----------------------------------------------------------------------
;-------------------------END STEP ONE-----------------------------------------
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
                ; STEP TWO) Normalize operands (or copy exponent)	
;------------------------------------------------------------------------------
		LD R1, expX		; load exponenet of x into R1
		LD R2, expY		; load exponent of y into R2
					; 2's complement math
		NOT R1, R1		
		ADD R1, R1, #1		
		ADD R3, R1, R2		; store result into R3
		BRn R1_GREATER_R2	; if R3 is negative, then R1x > R2y so jump
					; if R2y > R1x, R3 is positive
					; add the number of shifts to X's exponent
		LD R1, expX		; get R1 back to normal
		ADD R4, R1, R3		; add the expX to the shift needed amount
		ST R4, exponent_updated	; store the result of our updated exxponent
					; if zero or positive then shift X's mantissa to the right R3 times
		LD R1, valX		; load mantissa of X into R1
		ST R1, Param1
		ST R3, Param2		; put R3 (shift needed) into R2
		JSR right_shift
		LD R0, Result
		ST R0, valX		;store result of x shifted
		BR STEP2_DONE
;------------------------------------------------------------------------------
					; else
R1_GREATER_R2	NOT R3, R3		; R1x > R2y, R1 is negative
		ADD R3, R3, #1		; R3 (shift amount), get back to positive for shift counter

		LD R2, expY		; get R2 back to normal
		ADD R4, R2, R3		; add the Y exponent to the shift needed amount
		ST R4, exponent_updated	; store updated Y exponent
		LD R1, valY		; load Y mantissa
		ST R1, Param1
		ST R3, Param2		; put R3 (shift needed) into R2
		JSR right_shift
		LD R0, Result
		ST R0, valY		;store result of y shifted
STEP2_DONE
;------------------------------------------------------------------------------
;-----------------------------END STEP TWO-------------------------------------
;------------------------------------------------------------------------------
                ; STEP THREE) Convert operands to 2's complement
		LD R1, X
		BRp CHECK_Y
		LD R1, valX
		NOT R1, R1
		ADD R1, R1, #1
		ST R1, valX
CHECK_Y		LD R2, Y
		BRp STEP3_DONE
		LD R1, valY
		NOT R1, R1
		ADD R1, R1, #1
		ST R1, valY
STEP3_DONE
                ; STEP FOUR) Add mantissas
		LD R1, valX
		LD R2, valY
		ADD R3, R1, R2			; add the two mantissas
                BRp POSITIVE_MANTI		; STEP FIVE) Convert sum from 2's complement
		NOT R3, R3
		ADD R3, R3, #1
POSITIVE_MANTI  ST R3, Param1			; STEP SIX) Normalize sum , R3 = final added mantissa
		ST R3, valSum
		JSR left_most1			; set R3 to Param1 for left_most1 function
		LD R4, Result			; R4 contains left most 1 in the mantissa
		LD R5, TEN			; load the number ten
		NOT R5, R5			; make it negative
		ADD R5, R5, #1			; // 
		ADD R3, R5, R4			;insert normalized shift amount added to exponenet, should be negative here
		ST R3, norm_shift_amount
		ADD R2, R5, R4			; add the negative ten to left most bit position
		BRzp SHIFT_MANT_RI		; if zero or positive then left bit is >= 10, 
						; must shift mant to right and increase exponent
						; R2 is negative so 10 > left most bit, 
						; must shift mant left, decrease exponent
		NOT R2, R2			; make R2 positive
		ADD R2, R2, #1			; //
		ST R2, Param2			; R2 is shift amount for mantissa,
		LD R3, valSum			; Param1 still contains final mantissa
		ST R3, Param1
		JSR left_shift
						
		BR STEP6_FINAL
SHIFT_MANT_RI   ST R2, Param2			; R2 is shift amount for mantissa,
						; Param1 still contains final mantissa
		JSR right_shift
STEP6_FINAL	LD R1, Result			; R1 contains shifted final mantissa
		LD R3, norm_shift_amount	; lload R3 with the neg or positive shifted amount
		LD R4, exponent_updated		; normalized exponent
		ADD R3, R4, R3  		; add to exponent
;-----------------------------------------------------------------------------
                				; STEP SEVEN) Construct sum from fields
		ST R3, expSum			; store the exponenet sum
		LD R2, TEN			; load TEN mask into R2
		NOT R2, R2			; not mask to clear the tenth bit
		AND R1, R2, R1			; remove implicit one from R1(final mantissa)
		BRp MANTISSA_POS		; if mantissa is a positive value we jump
		NOT R1, R1			; make mantissa positive
		ADD R1, R1, #1			; //
		LD R4, ONE
		ST R4, signSum			; store the sign as one since its negative
MANTISSA_POS	ST R1, valSum
		AND R4, R4, #0
		ST R4, signSum			; store the sign as zero since its positive
		LD R0, valSum			; load mantissa into final result
		ST R3, Param1
		NOT R2, R2			; make TEN positive
		ST R2, Param2			; shift left ten times
		JSR left_shift
		LD R1, Result
		ST R1, Param1
		ST R0, Param2
		JSR binary_or			; or the mantissa and the exponenet together
		LD R0, Result
		LD R1, signSum
		BRz OR_SIGN_IN			; if R1 zero then we or nothing in, else we or the signmask in
		LD R1, SIGN_MASK		; put left most 1 in R1
OR_SIGN_IN	ST R1, Param1			; R1 contains zero
		JSR binary_or			; Result is now set
                LD R7,flt16_add_ra   ; restore return address
                RET
;------------------------------------------------------------------------------
flt16_sub       LD R3, Param1			; copy of param1
		LD R1, Param2			; Result is Param1 minus Param2
		ST R1, Param1			; store param2 as param1
		JSR flt16_neg
		LD R2, Result
		ST R3, Param1
		ST R2, Param2
		JSR flt16_add
                                     ; your code goes here
                RET
;------------------------------------------------------------------------------
;-----------------------------GET SIGN-----------------------------------------
;------------------------------------------------------------------------------
flt16_get_sign                       ; Result is 0 if Param1 is positive, 1 otherwise
                AND R0,R0,#0         	; Initialize result
                LD R1,Param1         	; Get first parameter
                BRzp ret_sign     	; Sign is 0 (zero or positive)
		ADD  R0,R0,#1		; negative
ret_sign     	ST R0, Result
                RET
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
;-----------------------------GET EXPONENT-------------------------------------
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
flt16_get_exp                        ; Result is biased exponent from Param1
		LD R2,TEN
		ST R2, Param2		; Param1 is already the needed value
		ADD R6, R7, #0
		JSR right_shift		; shift it over ten times
		ADD R7, R6, #0
		LD R0, Result
		LD R2,EXP_MASK			; load exponenetmask from memory
		AND R0, R0, R2
		ST R0, Result
                RET
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
;-----------------------------GET VALUE----------------------------------------
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
flt16_get_val   
                LD R1,Param1         ; Get first parameter
		LD R2, VAL_MASK		; load value mask
		AND R0, R2, R1		; and the mask against Param1
		BRz NO_DATA
		LD R3, IMPL1_MASK	; load implicit one mask
		NOT R3, R3		; or mask with result
		NOT R0, R0		; //
		AND R0, R0, R3		; //
		NOT R0, R0		; //
NO_DATA		ST R0, Result
                RET
;------------------------------------------------------------------------------
flt16_abs                            ; Result is absolute value of Param1
		LD R1,Param1         ; Get first parameter
		BRzp ABS_FINISH
		LD R3, SIGN_MASK
		NOT R3,R3
		AND R1, R3, R1
ABS_FINISH	ST R1, Result
                RET
;------------------------------------------------------------------------------
flt16_neg      
		LD R3, SIGN_MASK        ; 1 in left most position
		NOT R3, R3		; get zero in left most
		LD R1,Param1         ; Get first parameter
		BRz NEG_FINISH		; if zeros only, then return
		BRp POSITIVE_PARAM 

		AND R1, R1, R3
		BR NEG_FINISH
POSITIVE_PARAM	NOT R1, R1
		AND R1, R1, R3
		NOT R1, R1
NEG_FINISH	ST R1, Result
		RET
;------------------------------------------------------------------------------
left_most1                           ; Result is bit position of leftmost 1 in Param1
		ADD R6, R7, #0
		LD R4, SIXTEEN		; load R4 w/ 16 and counter backward
		ADD R4, R4, #-1		; decrement 16
		LD R0,Param1         ; Get first parameter
		BRn FINISH_LEFTMOST	; if R0 is zero or negative then jump
		LD R1, ONE		
		ST R1, Param2		; left shift once to the left
LOOP_SHIFT	JSR left_shift		; //
		ADD R4, R4, #-1		; decrement 16
		BRn FINISH_LEFTMOST
		LD R0, Result		; load shifted result of param1
		ST R0, Param1		; store shifted result to param1
		BRzp LOOP_SHIFT		; if shifted result is still positive then continue looping
FINISH_LEFTMOST ST R4, Result
		ADD R7, R6, #0
		RET
;------------------------------------------------------------------------------
left_shift                           ; Result is Param1 shifted left by Param2 bits
		LD R1,Param1         ; Get first parameter
		LD R2,Param2         ; Get second parameter, now our counter
		BRnz LEFT_SHI_RESULT		
LOOP_LEFT	ADD R1,R1,R1		; add R1 to itself to move left
		ADD R2,R2, #-1		; decrement counter
		BRp LOOP_LEFT
LEFT_SHI_RESULT	ST R1, Result
                RET
;------------------------------------------------------------------------------
right_shift 				; Result is Param1 shifted right by Param2 bits
 					; Algorithm: walk source and destination bit
		LD R0,Param1 		; load parameter
		LD R2,Param1 		; load parameter
		LD R1,Param2 		; load count
		BRnz return_rs 		; count must be positive
		AND R2,R2,#0 		; clear result
		LD R3,ONE 		; source mask = 1
		LD R4,ONE 		; destination mask = 1
rshift_loop1 	ADD R3,R3,R3 ; left shift source mask
		ADD R1,R1,#-1 		; decrement count
		BRp rshift_loop1 	; continue looping
 
rshift_loop2 	AND R5,R0,R3 ; source bit set?
		BRz rshift_next 	; not set, do nothing
		ADD R2,R2,R4 		; set, update result 
rshift_next 	ADD R4,R4,R4 ; shift destination mask
		ADD R3,R3,R3 		; shift source mask
		BRnp rshift_loop2 	; continue looping
return_rs 	ST R2,Result 	; store result
		RET

;------------------------------------------------------------------------------
binary_or                            ; Result is a bitwise OR of Param1 and Param2
		LD R1, Param1
		LD R2, Param2
		NOT R1, R1
		NOT R2, R2
		AND R0, R1, R2
		NOT R0, R0
		ST R0, Result
                RET
;------------------------------------------------------------------------------
                .END

