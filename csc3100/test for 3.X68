*-----------------------------------------------------------
* Title      : Test for 3 
* Written by : CALEB L
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    LEA $F12CE600,A0    LOADS INITIAL ADDRESS
    *UNCOMMENT BELOW LINES ACCORDINGLY*
    *ADDA.L #$1234,A0   *PART A
    *ADDA.W #$1234,A0   *PART B
    *ADDA.W #$4321,A0   *PART C
    SIMHALT             ; halt simulator

* Put variables and constants here

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
