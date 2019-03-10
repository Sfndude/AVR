uint8_t sensor=0, // 1 DAN 0
        counter=0;

#define BOLEH 1
#define TIDAK_BOLEH 0

void setup(){
    Serial.begin(9600);
    
    pinMode(5,OUTPUT); // CONVEYOR
    pinMode(6,OUTPUT); // PNEUMATIC
    pinMode(13,OUTPUT); // SIGN
    
    pinMode(3,INPUT_PULLUP); // SENSOR
    pinMode(4,INPUT_PULLUP); // RESET
}
void loop(){
    if(counter<10){
        if(digitalRead(3)==0){
            if(sensor==BOLEH)
                counter++;
            Serial.println("COUNTER = "+String(counter));
            sensor=TIDAK_BOLEH;
        }else if(digitalRead(3)!=0)
            sensor=BOLEH;
    }else{
        if(digitalRead(3)==0)
            Serial.println("CLICK RESET TO RESTART!");
    }
    
    if(digitalRead(4)==0){
        counter=0;
        Serial.println("COUNTER = "+String(counter));
    }
    delay(150);
}

