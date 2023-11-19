;
; Copyright (c) 2023, Arvid Juskaitis (arvydas.juskaitis@gmail.com)
;
; test int2str routine
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

;    jsr int2str
    #INT2STR num, buf, 10
end brk

    INT2STR_BUFFER_SIZE = 6
    .include "int2str.inc"

num .word 12345    ; $3039
buf .fill INT2STR_BUFFER_SIZE, 0

