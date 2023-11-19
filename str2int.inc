;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; string to int conversion routine/macro
; 64tass dialect
;

.weak
str2int_inc := true 
.endweak

.if str2int_inc
str2int_inc := false

    .cpu "6502"

; STR2INT str, num, 10
; prm1 - null terminated string
; prm2 - integer 
; prm3 - base (2-10)
STR2INT .macro  
    ; init str pointer
    lda #<\1
    sta $fb
    lda #>\1
    sta $fc
    ; set base
    lda #<\3
    sta mul16_num1
    lda #>\3
    sta mul16_num1+1
    jsr str2int
    ; copy result
    lda mul16_num2
    sta \2
    lda mul16_num2+1
    sta \2+1
    .endm 

; Func. str2int
; mul16_num1 loaded with base
; $fb points to input buffer
; result will be stored in mul16_num2
str2int
    ; init the index and running total variable
    ldy #0
    sty mul16_num2
    sty mul16_num2+1

str2int_loop
    lda ($fb),y
    beq str2int_done    ; it's done if it's null
    iny

    ; multipy number by base, copy result back to mul16_num2
    pha
    tya
    pha
    jsr mul16
    lda mul16_result    
    sta mul16_num2
    lda mul16_result+1
    sta mul16_num2+1
    pla
    tay
    pla

    ; translate PETSCII to binary, eg. '0' -> 0
    sec
    sbc #$30            

    ; add A value to total result
    clc
    adc mul16_num2
    sta mul16_num2
    lda #0
    adc mul16_num2+1
    sta mul16_num2+1

    jmp str2int_loop

str2int_done
    rts

    .include "mul.inc"

.fi ; str2int_inc

