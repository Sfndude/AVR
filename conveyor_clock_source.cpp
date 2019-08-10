#ifndef F_CPU
  #define F_CPU 16000000UL
#endif
#define MODE 1

#include <avr/io.h>
#include <util/delay.h>

uint8_t m_inc=0,m_dec=0;
uint8_t counter=0;

// active low and high segment
// common anode and cathode
const uint8_t segment[2][10]={
  {0x3f,0x06,0x5b,0x4f,0x66,
  0x6d,0x7d,0x07,0x7f,0x6f},
  {0xC0,0xF9,0xA4,0xB0,0x99,
  0x92,0x82,0xF8,0x00,0x10}
};
void write_segment(uint8_t index){ PORTD=((segment[MODE][index])<<1); }
void switch_segment(uint8_t index){
  if(index==0){
    PORTB|=(1<<1);
    PORTB&= ~(1<<0);
  }else{
    PORTB|=(1<<0);
    PORTB&= ~(1<<1);
  }
}
void write_number(uint8_t n){
  if(n<10){
    switch_segment(0);
    write_segment(0);
    _delay_ms(5);
    switch_segment(1);
    write_segment(n);
    _delay_ms(5);
  }else{
    switch_segment(0);
    write_segment((n/10));
    _delay_ms(5);
    switch_segment(1);
    write_segment(n-(int(n/10)*10));
    _delay_ms(5);
  }
}

int main(void){
  UCSR0B&= ~(1<<TXEN0);
  for(uint8_t x=1;x<8;x++)
    DDRD|=(1<<x);
  DDRB|=(1<<0)|(1<<1);
  PORTB|=(1<<2)|(1<<3);

  while(1){
    if((PINB & (1<<2))==0){
      if(m_inc!=0){
        if(counter>=99) counter=99;
        else counter++;
      }
      m_inc=0;
    }else if((PINB & (1<<2))!=0)
      m_inc=1;

    if((PINB & (1<<3))==0){
      if(m_dec!=0){
        if(counter<=0) counter=0;
        else counter--;
      }
      m_dec=0;
    }else if((PINB & (1<<3))!=0)
      m_dec=1;
    write_number(counter);
  }
}
