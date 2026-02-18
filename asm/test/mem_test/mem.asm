;=======================================================
;                       Memory test
;=======================================================
;
; - Copy a string (message ended with a NULL character)
; from the SRC_ADDR to DST_ADDR in data memory. 
; - Compare the content of memory between source and
; destination.
; - Print 'F' for test fail, 'S' for success.
;
;========================================================

; Assembler uses '=' to define label explicitly
SRC_ADDR=0x00000000
DST_ADDR=0x00000010

rst:
    add r0,0,r1             ; r1 is index
copy_loop:
    load r1,SRC_ADDR,r2     ; Load mem[SRC_ADDR+r1] into r2
    seq r2,0,r31            ; If r2=0 then r31=1, 0 otherwise
    branz r31,test          ; If r31=1, jmp to end, else continue
    store r1,DST_ADDR,r2    ; Store r2 into mem[DST_ADDR+r1]
    add r1,1,r1             ; Increment r1
    jmp copy_loop,r0        ; Loop again

test:
    add r0,0,r1             ; r1 is index
test_loop:
    load r1,SRC_ADDR,r2     ; Load mem[SRC_ADDR+r1] into r2
    load r1,DST_ADDR,r3     ; Load mem[DST_ADDR+r1] into r3
    seq r2,r3,r31           ; If r2=r3 then r31=1, 0 otherwise
    braz r31,test_fail
    seq r2,0,r31            ; If r2=0 then r31=1, 0 otherwise
    branz r31,test_ok       ; If r31=1, jmp to end, else continue
    add r1,1,r1             ; Increment r1
    jmp test_loop,r0        ; Loop again

test_fail:
    add r0,0x46,r1          ; r1 is 'F' (Fail)
    jmp print_result,r0

test_ok:
    add r0,0x53,r1          ; r1 is 'S' (Sucess)
    jmp print_result,r0

print_result:
    scall 3
    stop