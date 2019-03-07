#include <Arduino.h>
#define INCREASE 2
#define DECREASE 3
#define RESET 4

int counter=0, temp=0, inc=0,
    dec=0;

void setup(){
  Serial.begin(9600);
  PORTD|=(1<<2)|(1<<3)|(1<<4);
}
void loop(){
  if((PIND & (1<<INCREASE))==0){
    if(inc!=1)
      counter++;
    Serial.println("Counter = "+String(counter));
    inc=1;
  }else if((PIND & (1<<INCREASE))!=0)
    inc=0;

  if((PIND & (1<<DECREASE))==0){
    if(dec!=1)
      counter--;
    Serial.println("Counter = "+String(counter));
    dec=1;
  }else if((PIND & (1<<DECREASE))!=0)
    dec=0;

  if((PIND & (1<<RESET))==0){
    counter=0;
    Serial.println("RESET!");
    Serial.println("Counter = "+String(counter));
  }
  delay(50);
}