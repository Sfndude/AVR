// read button and turn on/off led
#define F_CPU 8000000
#include <avr/io.> // library for general purpose io register
#include <util/delay.h> // library for delay function

int main(){
	unsigned char mode=0;
	DDRB|=(1<<3); // set port b pin number 3 as output
	DDRB&=~(1<<4); // set port b pin number 4 as input

	while(1){
		if(PINB&(1<<4)){ // check pin condition
			if(mode==1) mode=0; // if mode status is 1 then change to 0
			else mode=1; // if mode status is 0 then change to 1
			_delay_ms(200); // delay for debouncing
		}

		if(mode==1) // check if mode is 1
			PORTB^=(1<<3); // flip bit condition on pin 3 to 1 or 0
	}
}
