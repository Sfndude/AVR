#include <Arduino.h>

volatile uint8_t ovf=0;

void init_timer1(){
  cli();
  TCCR1A=0x00;
  TCCR1B=0x00;

  TCNT1=0x85ed;
  TCCR1B|=(CS12);
  TIMSK1|=(1<<TOIE1);
  sei();
}

ISR(TIMER1_OVF_vect){
  if(ovf>=65){ // plus min 1000ms
    PORTB^=(1<<5);
    Serial.println("TIME = "+String(millis()/1000)+" | DATA "+analogRead(A0));
    ovf=0;
  }
  ovf++;
  TCNT1=0x85ed;
}

void setup(){
  Serial.begin(9600);

  init_timer1();
  DDRB|=(1<<5);
}
void loop(){}