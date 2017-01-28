*-----------------------------------------------------------
* Title      : Lab 6    
* Written by : Caleb Latimer
* Date       : 10/19/2016
* Description: Question 2
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    MOVE.B #1,D1
    ADD.B #2,D1
    ADD.B #9,D1
    ADD.B #7,D1
    
    LEA MESSAGE,A1
    MOVE.B #14,D0
    TRAP #15
        
    LEA MESSAGE2,A1
    MOVE.B #14,D0
    TRAP #15
    
    MOVE #3,D0
    TRAP #15


    SIMHALT             ; halt simulator

* Put variables and constants here
CR EQU $0D
LF EQU $0A
MESSAGE DC.B 'MY ACCESSID IS EJ1297',CR,LF,0
MESSAGE2 DC.B 'THE SUM IS ',0

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
