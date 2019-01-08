;read button and turn on led
;atmega328p
.device atmega328p
	rjmp INIT
INIT:
	ldi r16,0x08
	out 0x04,r16
	ldi r16,0x00
	out 0x05,r16
	ldi r16,0x10
	out 0x05,r16
MAIN:
	in r16,0x03
	out 0x05,r16
	rjmp MAIN
