;read button and turn on led
;atmega328p
.device atmega328p
	rjmp INIT	; first run
INIT:
	ldi r16,0x08	; load immediate r16 as 0b00001000
	out 0x04,r16	; set port b on pin 3 as output
	clr r16		; load immediate r16 as 0b00000000
	out 0x05,r16	; set all pins on port b to 0 (low)
	ldi r16,0x10	; load immediate r16 as 0b00010000
	out 0x05,r16	; set port b on pin 4 as input pullup
MAIN:
	in r16,0x03	; read status port b and copy the data to r16
	out 0x05,r16 	; write readed data to port b
	rjmp MAIN	; relative jump to label main (looping)
