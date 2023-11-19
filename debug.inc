;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; Routines could be usefull for debugging
; 64tass dialect
;

.weak
debug_inc := true 
.endweak

.if debug_inc
debug_inc := false

; Macro PRINT_HEX_VALUE col, row
; parm1 - col (0-39)
; parm2 - row (0-24)
; prints content of A register at col, row position 
PRINT_HEX_VALUE .macro
    ; save registers
    sta a + 1
    stx x + 1
    sty y + 1

    pha
    ; first nibble
    and #%00001111
    tay
    lda HEX,y
    sta $0400 + (\2 * 40) + \1 + 1

    pla
    ; second nibble
    and #%11110000
    lsr
    lsr
    lsr
    lsr
    tay
    lda HEX,y
    sta $0400 + (\2 * 40) + \1

    ; restore everything 
a  	lda #$00
x  	ldx #$00
y  	ldy #$00
    .endm

HEX	.byte $30, $31, $32, $33, $34, $35, $36, $37, $38, $39  ; 0-9
    .byte $01, $02, $03, $04, $05, $06                      ; A-F
    
.fi ; debug_inc
