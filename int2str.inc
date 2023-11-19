;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; Int to string conversion routines
; 64tass dialect
;

.weak
int2str_lib_inc := true 
INT2STR_BUFFER_SIZE = 5   ; buffer size excluding null terminator
.endweak

.if int2str_lib_inc
int2str_lib_inc := false

	.cpu "6502"

; INT2STR num, str, 10
; prm1 - integer to convert
; prm2 - string has to be null terminated
; prm3 - base (2-10)
INT2STR .macro  
    ; copy num
    lda \1
    sta div16_num1
    lda \1+1
    sta div16_num1+1
    ; set base
    lda #<\3
    sta div16_num2
    lda #>\3
    sta div16_num2+1
    ; init str pointer
    lda #<\2
    sta $fb
    lda #>\2
    sta $fc
    jsr int2str
    .endm 

; Func. int2str
; dividend contains initial value
; divisor contains base
; $fb points to output buffer
int2str
    ldy #INT2STR_BUFFER_SIZE-1  ; reverse index into buffer
int2str_loop
    tya
    pha
    jsr div16       ; div16_num1 contains quotient
    pla
    tay

    clc
    lda div16_rem
    adc #$30        ; translate to PETSCII

    sta ($fb),y
    dey
    bmi done        ; abort if buffer is too small

    ; check if there is value left
    lda div16_num1
    ora div16_num1+1
    bne int2str_loop

    ; fill in resten of buffer with spaces
    lda #" "
int2str_fill
    sta ($fb),y
    dey
    bmi done
    jmp int2str_fill
  
done    
    rts

    .include "div.inc"
        
.fi ; int2str_lib_inc

