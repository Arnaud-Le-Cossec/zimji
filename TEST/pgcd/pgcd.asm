;=======================================================
;                       PGCD
;=======================================================
;
; - Get two integers from console, a and b
; - Call euclide subroutine to calculate PGCD(a,b)
; - Print PGCD(a,b) on the console
;
;========================================================

; get a into r10
scall 0
add r1, 0, r10

; get b into r11
scall 0
add r1, 0, r11


; call euclide
jmp euclide, r30

; print result
add r10, 0, r1
scall 1

; Stop
stop

;= SUBROUTINE ===========================================

; Euclide
; @param a: r10
; @param b: r11
; @return PGCD(a,b): r10 (Return address in r30)

euclide:

; loop while a != b
seq r10, r11, r31
branz r31, euclide_return

; if a > b, then a=a-b
sle r10, r11, r31
branz r31, euclide_else

sub r10, r11, r10
jmp euclide, r0

euclide_else:
; else b=b-a
sub r11,r10,r11
jmp euclide, r0


; end of loop
euclide_return:
jmp r30,r0
