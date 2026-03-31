;=======================================================
;                       CHENILLARD
;=======================================================
;
; This program rotates a string in memory
;
;========================================================
BUFFER_ADDR=0
BUFFER_LEN=14
BUFFER_LEN_n_1=13

; Set buffer address into r2
add r0, BUFFER_ADDR, r2

main_loop:
    ; Display message
    add r2, 0, r1
    scall 4

    ; Save last character into r3
    load r2, BUFFER_LEN, r3         ; r3 = mem[r2 + 14]

    ; Init index and counter. We start before the last element
    add r2, BUFFER_LEN_n_1, r4         ; r4 = index (start at index 13)
    add r0, BUFFER_LEN, r5             ; r5 = counter (14 moves)

shift_right:
    load r4, 0, r6         ; Read from current index (ex: 13)
    store r4, 1, r6        ; Write at the next index  (ex: 14)
    
    sub r4, 1, r4           ; Decrement pointer toward left
    sub r5, 1, r5           ; Decrement le counter
    sle r5, 0, r31
    braz r31, shift_right

    ; Place back the last character in front (index 0)
    store r2, 0, r3

    ; Loop back
    jmp main_loop, r0




