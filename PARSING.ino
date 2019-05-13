String str;

void setup() {
    Serial.begin(9600);
    Serial.println("\nREADY TO RECEIVE COMMAND..");
    DDRB|=(1<<0)|(1<<1);
}

void loop() {
    if(Serial.available()>0){
        str=Serial.readStringUntil('\n');
        if(str=="11"){
            PORTB|=(1<<0);
            PORTB&= ~(1<<1);
            Serial.println("LED 1 ON\t|\tLED 2 OFF");           
        }else if(str=="22"){
            PORTB|=(1<<1);
            PORTB&= ~(1<<0);
            Serial.println("LED 1 OFF\t|\tLED 2 ON");           
        }else{
            PORTB&= ~ (1<<0);
            PORTB&= ~ (1<<1);
            Serial.println("Doesn\'t recognize command "+str);
        }
    }
}
