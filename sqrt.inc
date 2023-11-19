;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; Square root function
; inspired by https://dwheeler.com/6502/oneelkruns/asm1step.html
; 64tass dialect
;

.weak
sqrt_inc := true 
.endweak

.if sqrt_inc
sqrt_inc := false

    .cpu "6502"

; Func. sqrt16
; sqrt16_num - put 16-bit number for input
; sqrt16_num - lsb contains square root, msb - remainder
sqrt16
    ldy #$01            ; lsby of first sqrt16_odd sqrt16_number = 1
    sty sqrt16_odd
    dey
    sty sqrt16_odd+1    ; msby of first sqrt16_odd sqrt16_number (sqrt = 0)
sqrt16_loop   
    sec
    lda sqrt16_num      ; save remainder in x register
    tax                 ; subtract sqrt16_odd lo from integer lo
    sbc sqrt16_odd
    sta sqrt16_num
    lda sqrt16_num+1    ; subtract sqrt16_odd hi from integer hi
    sbc sqrt16_odd+1
    sta sqrt16_num+1    ; is subtract result negative?
    bcc sqrt16_done     ; no. increment square root
    iny
    lda sqrt16_odd      ; calculate next sqrt16_odd sqsrt16_number
    adc #$01
    sta sqrt16_odd
    bcc sqrt16_loop
    inc sqrt16_odd+1
    jmp sqrt16_loop
sqrt16_done 
    sty sqrt16_num      ; all done, store square root
    stx sqrt16_num+1    ; and remainder
    rts

sqrt16_num .word 0
sqrt16_odd .word 0

.fi ; sqrt_inc

