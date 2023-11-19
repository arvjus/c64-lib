;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; C64 specific stuff
; 64tass dialect
;

.weak
c64_inc := true 
.endweak

; unused mem locations 2, 251, 252, 253, 254 ($02, $FB, $FC, $FD, $FE)
; timer $a0-$a2  1/60 jitter


.if c64_inc
c64_inc := false

; Memory locations
C64_SCREEN		    = $0400
C64_COLOUR		    = $D800
C64_BORDER_COLOUR	= $D020
C64_SCREEN_COLOUR	= $D021
C64_SCREEN_CASE	    = $D018 ; 21 - upper, 23 - lower
C64_CURSOR_POS      = $00d6 ; ??
C64_CURSOR_CTRL     = $00cc
C64_CURSOR_COLOUR   = $0286

; KERNAL Subroutines
C64_CHRIN           = $ffe4
C64_CHROUT          = $ffd2
C64_PRINT_LINE      = $ab1e
C64_CLEAR_SCREEN    = $e544
C64_HOME_CURSOR     = $e566
C64_PLOT            = $fff0 ; set/get cursor pos

; Colour constans
BLACK	            = 0
WHITE	            = 1
RED	                = 2
CYAN	            = 3
PURPLE	            = 4
GREEN	            = 5
BLUE	            = 6
YELLOW	            = 7
ORANGE	            = 8
BROWN	            = 9
LIGHT_RED	        = 10
DARK_GREY	        = 11
GREY    	        = 12
LIGHT_GREEN	        = 13
LIGHT_BLUE          = 14
LIGHT_GREY          = 15

; POKE address, value
; prm1 - address
; prm1 - value
POKE .macro  
    lda #\2
    sta \1
    .endm 


.fi ; c64_inc

