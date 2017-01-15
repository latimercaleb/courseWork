*-----------------------------------------------------------
* Program    : LAB 9
* Written by : CALEB LATIMER
* Date       : 11/9/2016
* Description: ARRAY MANIPULATION
*-----------------------------------------------------------
	ORG	$1000
START:				; first instruction of program

	LEA	PARTA, A1	//PRINT PARTA
	MOVE.B	#14,D0		//display the original string
	TRAP	#15
	CLR.L	D1
	LEA     ARRAY,A1        LOAD ARRAY TO A1
	CLR.L   D3               CLEARS COUNT REGISTER
	CLR.L   D4                  CLEARS EVEN REGISTER
	CLR.L   D5               CLEARS ODD REGISTER
	CLR.L   D6                 CLEARS INDEX COUNTER
	
LOOP	
        MOVE.B	(A1)+,D1
        ADD.B   #1,D6
        AND     #1,D6
        BEQ     ADDTOEVEN
        BNE     ADDTOODD
        
COMPARE   
        CMP.B   #10,D1
        BGT     INCREMENT
	BRA	PRINTSPACE		//if a period is identified, jump out the loop.
	
RETURN
	MOVE	#3, D0		//if it is neither a space nor a period, display the character
	TRAP	#15
	CMP.B   #16,D1
	BEQ     DONE
	BRA	LOOP
			
PRINTSPACE
        MOVE.L A1,A3
        LEA TAB,A1
        MOVE.B #14,D0
        TRAP #15
        MOVE.L A3,A1
        BRA     RETURN 
        
INCREMENT
        ADD.B   #1,D3
        BRA     PRINTSPACE
        
ADDTOEVEN
       ADD.B D1,D4
        BRA COMPARE
        
ADDTOODD
        ADD.B D1,D5
        BRA COMPARE
	
DONE	
        LEA NEWL,A1
        MOVE.B #14,D0
        TRAP    #15
        
        LEA     PARTB,A1
        MOVE    #14,D0
        TRAP #15
        
        MOVE.L  D3,D1
        MOVE.B  #3,D0
        TRAP    #15
        
        LEA NEWL,A1
        MOVE.B #14,D0
        TRAP    #15
        
        LEA     PARTCO,A1
        MOVE    #14,D0
        TRAP #15
        
        MOVE.L  D5,D1
        MOVE.B  #3,D0
        TRAP    #15
        
        LEA NEWL,A1
        MOVE.B #14,D0
        TRAP    #15

        
        LEA     PARTCE,A1
        MOVE    #14,D0
        TRAP #15
        
        MOVE.L  D4,D1
        MOVE.B  #3,D0
        TRAP    #15


        MOVE.B	#9,D0
	TRAP	#15

* Variables and Strings
CR	EQU	$0D
LF	EQU	$0A
ARRAY	DC.B	5,7,12,3,8,21,11,1,2,16
NEWL	DC.B	'',CR,LF,0
TAB     DC.B     ' ',0
PARTA   DC.B    'Part A',CR,LF,0
PARTB   DC.B    'Part B: ',0
PARTCO   DC.B    'Part C ODD: ',0
PARTCE   DC.B    'Part C EVEN: ',0


	END	START		; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
