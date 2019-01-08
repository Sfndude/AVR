// blink example for pin number 3 at PORTB
#define F_CPU 8000000UL
#include <avr/io.h> // library for general purpose io register
#include <util/delay.h> // library for delay function

int main(){
	DDRB|=(1<<3); // set pin 3 at port b as output
	while(1){
		PORTB^=(1<<3); // flip bit at register 3 to 1 or 0
		_delay_ms(250); // delay time for 250 milliseconds
	}
}
