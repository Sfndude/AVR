#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#define UBRR 9600
#define BAUDRATE ((F_CPU)/(UBRR*16UL)-1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

volatile uint8_t ovf=1;
volatile char msg[8];

void init_uart(void){
  UBRR0L=(BAUDRATE);
  UBRR0H=(BAUDRATE>>8);
  UCSR0B|=(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
}
void uart_put(char c){
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0=c;
}
void uart_puts(char* s){
  uint8_t len=0;
  char* temp=s;

  while(*temp!=0){
    len++;
    temp++;
  }
  for(int x=0;x<len;x++)
    uart_put(s[x]);
}

void init_timer1(void){
  TCCR1B|=(1<<CS10)|(1<<CS11)|(1<<CS12);
  TCNT1=65534;
  TIMSK1|=(1<<TOIE1);
  sei();
}

ISR(TIMER1_OVF_vect){
  TCNT1=65534;

  if(ovf>10) uart_puts("JOB ENDED!\n");
  else{
    itoa(ovf,msg,10);
    PORTB|=(1<<5);
    uart_puts("COUNTER = ");
    uart_puts(msg);
    uart_put('\n');
    ovf++;
    PORTB&= ~(1<<5);
  }
}

int main(void){
  DDRB|=(1<<5)|(1<<4);
  PORTD|=(1<<5)|(1<<4);
  init_uart();
  init_timer1();
  uart_puts("READY TO RUN COMMAND!\n");

  while(1);
}