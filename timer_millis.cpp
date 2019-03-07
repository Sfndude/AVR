#include <Arduino.h>

int overflow=0,temp=0;

void setup(){
  Serial.begin(9600);
  Serial.println("Data Sensor Reading.. ");
}
void loop(){
  overflow=(millis()/100);
  if(overflow==temp){
    Serial.println(String(overflow)+":"+String(analogRead(A0)));
    temp=overflow+1;
  }
}