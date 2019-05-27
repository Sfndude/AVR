#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#define PASSWORD "sfndude"
#define MEM 128

Servo s;
String str_tmp;
uint8_t chance=3;
int timer=0;

void run_security_sys();
void init_security();

void setup(){
  pinMode(2,INPUT_PULLUP);
  pinMode(4,OUTPUT);
  s.attach(3);
  EEPROM.begin();
  Serial.begin(9600);

  init_security();
}
void loop(){run_security_sys();}

void run_security_sys(){
  if(Serial.available()>0){
    str_tmp = Serial.readStringUntil('\n');

    if(EEPROM.read(MEM)>=1){
      if(str_tmp!=PASSWORD){
        chance--;
        EEPROM.update(MEM,chance);
        Serial.println(str_tmp);
        Serial.println("[-] System is failed to unlock!");
        Serial.println("[info] Retry number : "+String(EEPROM.read(MEM)));
  
        init_security();
      }else{
        digitalWrite(4,LOW);
        Serial.println(str_tmp);
        Serial.println("[+] System is succesfully unlocked!");
        s.write(0);
        //timer = (millis()/1000);
        delay(5000);
        //if(timer>=5)
          s.write(90);
        chance=3;
        EEPROM.update(MEM,chance);
      }
    }else{
      digitalWrite(4,HIGH);
      Serial.println("[-] System is blocked!");
      if(digitalRead(2)==LOW){
        EEPROM.update(MEM,3);
        digitalWrite(4,LOW);
        init_security();
      }
    }
  }
}
void init_security(){
  s.write(90);
  if(EEPROM.read(MEM)>=1){
    Serial.println("----------===[SECURITY]===----------");
    Serial.println("[info] Retry number : "+String(EEPROM.read(MEM)));
    Serial.println("[info] Please enter the password");
    Serial.print("> ");
  }else{
    digitalWrite(4,HIGH);
    Serial.println("[-] System is blocked!");
    if(digitalRead(2)==LOW){
      EEPROM.update(MEM,3);
      digitalWrite(4,LOW);
      init_security();
    }
  }
}
