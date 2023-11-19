;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test stdio-lib routines
; 64tass dialect
;

INPUT_STRING_BUFFER_SIZE = 15

	.cpu "6502"

; BASIC loader (10 SYS 2064)
*	= $0801
	.word (+), 10
	.text $9e, format("%d", start), 0
+	.word 0

*	= $0810

start

    #SCREEN_LOWER_CASE 
    #CURSOR_ON
    #MOVE_CURSOR 1, 5
    #SET_CURSOR_COLOUR GREY
    #SET_INPUT_HANDLER digits_only
    
l1
    lda #"?"
    jsr C64_CHROUT
    jsr input_string
   	
    lda #"!"
    jsr C64_CHROUT
 	
    lda #<is_buffer
	ldy #>is_buffer
    jsr C64_PRINT_LINE

    lda #$0d
    jsr C64_CHROUT

    jmp l1

end brk

; set CF if A contains anything else than a digit
digits_only
    pha
    sbc #$2f    ; '0' -> 1, '1' -> 2, etc.
    cmp #11     ; '9' and below
    pla
    rts

	.include "c64.inc"
    .include "stdio.inc"
