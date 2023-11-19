;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; Multiplication functions
; Inspired by https://llx.com/Neil/a2/mult.html
; 64tass dialect
;

.weak
mul_lib_inc := true 
.endweak

.if mul_lib_inc
mul_lib_inc := false

    .cpu "6502"

; Func. mul8
; Destroys mul8_num2
mul8
    lda #0                  ; initialize mul8_result to 0
    sta mul8_result
    sta mul8_result+1
    
    ldx #8                  ; number of bits in mul8_num2
mul8_loop:
    lsr mul8_num2
    bcc mul8_no_add
    clc
    adc mul8_num1
mul8_no_add:
    ror                     ; "Stairstep" shift (catching carry from add)
    ror mul8_result
    dex
    bne mul8_loop
    sta mul8_result+1
    rts

mul8_num1   .byte 0
mul8_num2   .byte 0
mul8_result .word 0

; Func. mul16
; Destroys mul16_num2
mul16
    lda  #0
    sta  mul16_result       ; initialize the RESULT
    sta  mul16_result+1
    sta  mul16_result+2
    sta  mul16_result+3

    ldx  #16                ; we'll loop 16 times.
mult16_loop
    lsr mul16_num2+1        ; get low bit of NUM2
    ror mul16_num2
    bcc mult16_no_add       ; 0
    tay                     ; 1,  add NUM1 (hi byte of RESULT is in A)
    clc
    lda mul16_num1
    adc mul16_result+2
    sta mul16_result+2
    tya
    adc mul16_num1+1
mult16_no_add
    ror
    ror mul16_result+2
    ror mul16_result+1
    ror mul16_result
    dex                 
    bne mult16_loop    
    sta mul16_result+3
    rts

mul16_num1      .word 0
mul16_num2      .word 0
mul16_result    .word 0, 0

.fi ; mul_lib_inc

