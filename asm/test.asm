;; comment

add r0,0,r2

label_while:
    scall 0
    add r2,r1,r2
    jmp label_while, r0