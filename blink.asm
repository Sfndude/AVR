; atmega328p
; turn on example at pin 3
.device atmega328p
	ldi r16,0x08	; set register r16 with 0x08 = 0b00001000
	out 0x04,r16	; set register DDRB on pin 3 as output
	out 0x05,r16	; set register PORTB on pin 3 to high/1
Start:
	rjmp Start	; jump to label Start
