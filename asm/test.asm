;; comment

add r0,0,r2

label_while:
    scall 0
    add r2,r1,r2
    add r2,0,r1
    scall 1
    jmp label_while, r0