*-----------------------------------------------------------
* Title      : Caleb Latimer
* Written by : Lab 8 
* Date       : 11/2/2016
* Description: Lab 8(loop)
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    MOVE.B      #0,D1   ;X = D1
    MOVE.B      #1,D2   ; Y = D2
    
    
while
    CMP     #10,D1 ; compare X with 10
    BLE     if     ; if x <= 10 do if
    BGT     end    ; if not exit while() do end  
                   
if
    MOVE.L D1,D3
    DIVU #2,D3
    SWAP D3
    CMP #0,D3
    BEQ executeif
    BNE else

executeif
    MULS D1,D2
    ADD     #1,D1
    BRA while
    
else                        
    ADD     #1,D2
    ADD     #1,D1
    BRA while

    
end
    MOVE.B  #14,D0      ;Display the ending message
    LEA     result,A1
    TRAP    #15
    
    MOVE.L   D2,D1
    MOVE.L   #3,D0
    TRAP     #15

    SIMHALT             ; halt simulator

* Put variables and constants here
result DC.B 'The result is: ',0

    
    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
