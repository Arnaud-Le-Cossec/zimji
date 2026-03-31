;=======================================================
;                       ADVENTURE
;=======================================================
;
; - Small adventure game
;
;========================================================

MSG_INTRO=0x00 ;  "You are in a dungeon. 1: North, 2: West"
MSG_WIN=0x30   ; "Well done! You've found the way out."
MSG_LOSE=0x60  ; "A trap is triggered... Game Over."
MSG_DRAGON=0x90 ; "You are in a room with a sleepy dragon. 1: East, 2: Attack"

main:
    ; Display intro message
    add r0, MSG_INTRO, r1
    scall 4

main_loop:
    ; Read user choice
    scall 0

    ; Test if choice 1 (North gate) then jump to 'win'
    seq r1, 1, r31
    branz r31, dragon

    ; Test if choice 1 (West gate) then jump to 'lose'
    seq r1, 2, r31
    branz r31, lose

    ; Else, jump back
    jmp main_loop, r0

dragon:
    ; Display dragon message
    add r0, MSG_DRAGON, r1
    scall 4

dragon_loop:
    ; Read user choice
    scall 0

    ; Test if choice 1 (East gate) then jump to 'main'
    seq r1, 1, r31
    branz r31, main

    ; Test if choice 1 (Porte Droite) then jump to 'lose'
    seq r1, 2, r31
    branz r31, win

    ; Else, jump back
    jmp dragon_loop, r0

win:
    ; Display win message
    add r0, MSG_WIN, r1
    scall 4
    jmp end, r0

lose:
    ; Display game over message
    add r0, MSG_LOSE, r1
    scall 4
    jmp end, r0

end:
    stop