*-----------------------------------------------------------
* Title      : Test for 4
* Written by : Caleb L.
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    CLR D0
    MOVE.B D0, D1
    MOVE.B #10, D2
XXX    ADD.B D2, D0
    ADD.B #1, D1
    ADD.B D1, D0
    SUB.B #1, D2
    BNE XXX     Same code from problem
    
    MOVE.L D0,D3
    MOVE.L D1,D4
    MOVE.L D2,D5    Copies results to unused registers
    
    LEA MSG1,A1
    MOVE #14,D0
    TRAP #15    
    
    MOVE.L D3,D1
    MOVE #3,D0
    TRAP #15    First prompt sequence outputs the result of D0
    
    LEA MSG2,A1
    MOVE #14,D0
    TRAP #15
    
    MOVE.L D4,D1
    MOVE #3,D0
    TRAP #15    Second prompt sequence outputs result of D1


    LEA MSG3,A1
    MOVE #14,D0
    TRAP #15    
    
    MOVE.L D5,D1
    MOVE #3,D0
    TRAP #15    Third prompt sequence outputs result of D2 


    

    SIMHALT             ; halt simulator

* Put variables and constants here
LF  EQU  $0A
CR  EQU  $0D 
MSG1 DC.B 'D0 = ' ,0
MSG2 DC.B 'D1 = ' ,0
MSG3 DC.B 'D2 = ', 0

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
