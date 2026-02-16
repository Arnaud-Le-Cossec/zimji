;=======================================================
;                         Speed test
;=======================================================
;
; Just loop 100.000 times
;
;========================================================

rst:
    add r0,0,r10            ; r10 is tmp
loop:
    jmp wait,r31            ; go to subroutine
    seq r10,100,r11       ; r10 = 65535 ? if true then r11=1
    branz r11,end           ; if r11=1, jmp to end
    add r10,1,r10           ; else increment
    jmp loop,r0             ; and loop again
end:
    stop r                  ; Stop simulator

wait:
    add r0,0,r1             ; r1 is tmp
wait_loop:
    seq r1,10,r4         ; r1 = 65535 ? if true then r4=1
    branz r4,wait_end       ; if r4=1, jmp to wait_end
    add r1,1,r1             ; else increment
    jmp wait_loop,r0        ; and loop again
wait_end:
      jmp r31,r0            ; retour de fonction