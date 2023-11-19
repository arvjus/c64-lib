;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; Console input/output routines/macros
; 64tass dialect
;

.weak
stdio_lib_inc := true 
INPUT_STRING_BUFFER_SIZE = 10   ; buffer size incluing null terminator
.endweak

.if stdio_lib_inc
stdio_lib_inc := false

    .cpu "6502"

; Cursor control macros ********
;

; ------------------------------
; Macro CURSOR_ON
; ------------------------------
CURSOR_ON .macro
    lda #0
    sta C64_CURSOR_CTRL
    .endm

; ------------------------------
; Macro CURSOR_OFF
; ------------------------------
CURSOR_OFF .macro
    lda #1
    sta C64_CURSOR_CTRL
    .endm

; ------------------------------
; Macro MOVE_CURSOR col, row
; parm1 - col (0-39)
; parm2 - row (0-24)
; ------------------------------
MOVE_CURSOR .macro
    clc
    ldy #\1
    ldx #\2
    jsr C64_PLOT
    .endm

; ------------------------------
; Macro SET_CURSOR_COLOUR val
; parm1 - colour
; ------------------------------
SET_CURSOR_COLOUR .macro
    lda #\1
    sta C64_CURSOR_COLOUR
    .endm


; Output routines/macros ********
;

; SCREEN_UPPER_CASE 
SCREEN_UPPER_CASE .macro
    lda #21
    sta C64_SCREEN_CASE
    .endm

; SCREEN_LOWER_CASE 
SCREEN_LOWER_CASE .macro
    lda #23
    sta C64_SCREEN_CASE
    .endm


; Input routines/macros ********
;


; ------------------------------
; Macro SET_INPUT_HANDLER my_handler
; prm1 - handle address
;
; Custom routine for input filtering
; A contains last char
; Set CF in order to ignore the character
; ------------------------------
SET_INPUT_HANDLER .macro
    lda #<\1
    sta is_handler+1
    lda #>\1+1
    sta is_handler+2
    .endm


; ------------------------------
; Func. input_string
; Reads input until CR is pressed, null terminates on RETURN
; Usage:
; 	lda #<buf
;	ldy #>buf
;	jsr input_string
; ------------------------------
input_string
    lda #0
    sta is_index	; reset index
is_next_char
    ; get and display char
    jsr C64_CHRIN
    beq is_next_char
    ; special keys
    cmp #$14		; Back/Del
    beq is_back
    cmp #$03		; ESC/Break
    beq is_done
    cmp #$0d		; Enter
    beq is_done
    ; filter input 
is_handler
    jsr is_default_handler
    bcs is_next_char
    ; display char
    jsr C64_CHROUT
    ; store to output
    ldy is_index
    sta is_buffer,y
    inc is_index
    ; check limits
    lda is_index
    cmp #INPUT_STRING_BUFFER_SIZE-1
    bcc is_next_char
    
is_done				; null terminate output and exit
    lda #0
    ldy is_index
    sta is_buffer,y
    rts

is_back				; remove last char if any
    jsr C64_CHROUT
    lda #0
    cmp is_index
    beq is_next_char
    dec is_index
    jmp is_next_char

is_default_handler
    clc
    rts

is_index
    .byte 0
is_buffer
    .fill INPUT_STRING_BUFFER_SIZE, 0	
    
    .include "c64.inc"

.fi ; stdio_lib_inc

