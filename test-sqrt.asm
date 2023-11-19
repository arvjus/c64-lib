;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test sqrt16 routine
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

    ; sqrt(12345) = 111 ;24  - sqrt($3039) = $6f ;$18
    lda #<12345
    sta sqrt16_num
    lda #>12345
    sta sqrt16_num+1
    jsr sqrt16    
end brk

    .include "sqrt.inc"

