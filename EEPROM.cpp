#include <Arduino.h>
#include <EEPROM.h>
#define MEM 126

volatile uint8_t stat;

void read_latest(){
  uint8_t data = EEPROM.read(MEM);

  if(data!=0) digitalWrite(LED_BUILTIN,HIGH);
  else digitalWrite(LED_BUILTIN,LOW);

  Serial.println("SAVED : "+String(data));
  delay(3);
}

void update(){
  if(stat==1) stat=0;
  else stat=1;

  EEPROM.update(MEM,stat);

  Serial.println("DATA : "+String(stat));
  digitalWrite(LED_BUILTIN,stat);
  delay(3);
}

void setup(){
  Serial.begin(9600);
  EEPROM.begin();
  Serial.println("\nREADY..");

  pinMode(2,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);

  read_latest();
  attachInterrupt(digitalPinToInterrupt(2),update,FALLING);
}
void loop(){}