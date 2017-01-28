*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    
   MOVE #16,D2
   MOVE #3,D1
   DIVU D1,D2
    STOP #$2700 
 
  
    SIMHALT             ; halt simulator

* Put variables and constants here
X   DS.L    1    
    END    START        ; last line of source
     ;MOVE.L  $F12CE600,A0
    ;ADDA.L #$1234,A0
    ;ADDA.W #$1234,A0
    ;ADDA.W #$4321,A0 

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
