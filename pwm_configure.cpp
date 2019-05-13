#include <Arduino.h>

uint8_t lbt=0,rbt=0,
        statl=0,statr=0,
        valL,valR;

void setup(){
    PORTB |= (1<<0)|(1<<1);
    DDRB |= (1<<2)|(1<<3);

    Serial.begin(9600);
    Serial.println("\n-=[ Ready to receive job ]=-\n");
}
void loop(){
    if((PINB & (1<<0))==0){
        if(lbt==1){
            if(statl==0){
                Serial.println("[*] Configuring LED 1");
                statl=1;
            }else if(statl!=0){
                Serial.println("[+] LED 1 Configured!");
                statl=0;
            }
        }
        lbt=0;
    }else if(PINB & (1<<0)!=0)
        lbt=1;

    if((PINB & (1<<1))==0){
        if(rbt==1){
            if(statr==0){
                Serial.println("[*] Configuring LED 2");
                statr=1;
            }else if(statr!=0){
                Serial.println("[+] LED 2 Configured!");
                statr=0;
            }
        }
        rbt=0;
    }else if(PINB & (1<<1)!=0)
        rbt=1;

    if(statl==1){
        valL=map(analogRead(A0),0,1023,0,255);
        analogWrite(10,valL);
        Serial.println("[*] LED 1 = "+String(valL));
    }

    if(statr==1){
        valR=map(analogRead(A0),0,1023,0,255);
        analogWrite(11,valR);
        Serial.println("[*] LED 2 = "+String(valR));
    }
    delay(150);
}