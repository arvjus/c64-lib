;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; wait for key press, print hex value on screen
; 64tass dialect
;

    .cpu "6502"

; BASIC loader (10 SYS 2064)
*	= $0801
    .word (+), 10
    .text $9e, format("%d", start), 0
+	.word 0

*	= $0810

start

l1	jsr C64_CHRIN
    beq l1
    #PRINT_HEX_VALUE 38, 24
    cmp #3			; ESC
    bne l1
    rts

    .include "c64.inc"
    .include "debug.inc"
