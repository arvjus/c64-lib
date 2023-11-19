;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test str2int routine
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

    #STR2INT buf, num, 10
end brk

    .include "c64.inc"
    .include "str2int.inc"

num .word 0
buf .text "12345", 0    ; $3039

