*-----------------------------------------------------------
* Title      : Lab 6
* Written by : Caleb Latimer
* Date       : 10/19/2016
* Description: Question 1 
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    LEA MESSAGE,A1
    MOVE.B #14,D0
    TRAP #15
    MOVE.B #9,D0
    TRAP #15

    SIMHALT             ; halt simulator

* Put variables and constants here
CR EQU $0D
LF EQU $0A
MESSAGE DC.B 'HELLO',CR,LF
        DC.B 'WORLD',0

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
