;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test mulxx routines
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

    ; 123 * 35 = 4305  - $7b * $23 = $10d1
    lda #123
    sta mul8_num1
    lda #35
    sta mul8_num2
j1  jsr mul8
r1  nop

    ; 12345 * 54321 = 670592745  - $3039 * $d431 = $27f86ee9
    lda #<12345
    sta mul16_num1
    lda #>12345
    sta mul16_num1+1
    lda #<54321
    sta mul16_num2
    lda #>54321
    sta mul16_num2+1
j2  jsr mul16
r2  nop

end brk

    .include "mul.inc"

