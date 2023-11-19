;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test divxx routines
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

    ; 1234 / 5 = 246; 4   - $04d2 / $005 = $00f6; $0004
    lda #<1234
    sta div16_num1
    lda #>1234
    sta div16_num1+1
    lda #<5
    sta div16_num2
    lda #>5
    sta div16_num2+1
div jsr div16

end brk

   .include "div.inc"

