//#include <Arduino.h> // UNCOMMENT THIS IF YOU NOT USING ARDUINO IDE
#define INCREASE 2
#define DECREASE 3
#define RESET 4

int counter=0, inc=0,
    dec=0;

void setup(){
  Serial.begin(9600);
  for(int x=2;x<4;x++)
      pinMode(x,INPUT_PULLUP);
}
void loop(){
  if(digitalRead(INCREASE)==0){
    if(inc!=1)
      counter++;
    Serial.println("Counter = "+String(counter));
    inc=1;
  }else if(digitalRead(INCREASE)!=0)
    inc=0;

  if(digitalRead(DECREASE)==0){
    if(dec!=1)
      counter--;
    Serial.println("Counter = "+String(counter));
    dec=1;
  }else if(digitalRead(DECREASE)!=0)
    dec=0;

  if(digitalRead(RESET)==0){
    counter=0;
    Serial.println("RESET!");
    Serial.println("Counter = "+String(counter));
  }
  delay(100);
}
