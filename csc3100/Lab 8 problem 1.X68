*-----------------------------------------------------------
* Title      : Lab 8
* Written by : Caleb Latimer
* Date       : 11/2/2016
* Description: Conditionals(part 1)
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    MOVE.B  #14,D0      ;Display the starting message
    LEA     prompt,A1
    TRAP    #15

    MOVE.B  #4,D0       ;Load X (stored in D1.L)
    TRAP    #15

    CMP #12,D1            ;compare X to 12
    
    BGT if             ;BGT: greater than
                        ;if X>12, jump to branch labeled if
                        ;else, do nothing
                        
    BLE else            ;BLE: less than or equal to
                        ;if X<=12, jump to branch else
                        ;else, do nothing
  
else                        
    SUB #13,D1
    BRA end           ;jump to branch end
    
if
    MULS    #2,D1
    ADD     #4,D1
    
end
    MOVE.B  #14,D0      ;Display the ending message
    LEA     result,A1
    TRAP    #15
    
    MOVE.L   #3,D0
    TRAP     #15

    SIMHALT             ; halt simulator

* Put variables and constants here
prompt DC.B 'Enter a number for X: ',0
result DC.B 'The resulting X is: ',0

    
    END    START        ; last line of source


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
