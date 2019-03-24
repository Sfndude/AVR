#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

uint8_t m_inc=0,m_dec=0;
uint8_t counter=0;

// active high segment
const uint8_t segment[10]={
  0x3f,0x06,0x5b,0x4f,0x66,
  0x6d,0x7d,0x07,0x7f,0x6f
};
void write_segment(uint8_t index){ PORTD=segment[index]; }
void switch_segment(uint8_t index){
  if(index==0){
    PORTB|=(1<<0);
    PORTB&= ~(1<<1);
  }else if(index==1){
    PORTB|=(1<<1);
    PORTB&= ~(1<<0);
  }
}
void write_number(uint8_t n){
  if(n<10){
    switch_segment(0);
    write_segment(0);
    _delay_ms(3);
    switch_segment(1);
    write_segment(n);
    _delay_ms(3);
  }else{
    switch_segment(0);
    write_segment((n/10));
    _delay_ms(3);
    switch_segment(1);
    write_segment(n-(int(n/10)*10));
    _delay_ms(3);
  }
}

int main(void){
  for(uint8_t x=0;x<8;x++)
    DDRD|=(1<<x);
  DDRB|=(1<<0)|(1<<1);
  PORTB|=(1<<2)|(1<<3);

  while(1){
    if((PINB & (1<<2))==0){
      if(m_inc!=0){
        if(counter>=99) counter=99;
        write_number(counter);
        counter++;
      }
      m_inc=0;
    }else if((PINB & (1<<2))!=0)
      m_inc=1;

    if((PINB & (1<<3))==0){
      if(m_dec!=0){
        if(counter<=0) counter=0;
        write_number(counter);
        counter--;
      }
      m_dec=0;
    }else if((PINB & (1<<3))!=0)
      m_dec=1;

    _delay_ms(150);
  }
}