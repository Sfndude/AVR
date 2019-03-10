#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h> // itoa
//#define _cast(x) #x

#define CONVEYOR_TIMER 10
#define PNEUMATIC_TIMER 2

#define UBBR 9600
#define BAUDRATE ((F_CPU)/(UBBR*16UL)-1)

#define SENSOR 3
#define RESET 4
#define CONVEYOR 5
#define PNEUMATIC 6

volatile uint8_t sensor=0,job=0,counter=0;
volatile char num2ch[8];

/**************USART****************/
void init_uart(void){
  UBRR0L=(BAUDRATE);
  UBRR0H=(BAUDRATE>>8);
  UCSR0B|=(TXEN0);
  UCSR0C|=(1<<UCSZ00)|(UCSZ01);
}

void uart_put(char ch){
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0=ch;
}

void uart_puts(char* txt){
  int len=0;
  char* temp=txt;

  while(*temp!=0){
    temp++;
    len++;
  }

  for(int x=0;x<len;x++)
    uart_put(txt[x]);
}
/******************************/

/**************TIMER****************/
void init_timer1(void){
  OCR1A=15625; // top value
  //_SFR_MEM16(0x88)=15625;
  TCCR1B|=(1<<WGM12)|(1<<CS12)|(1<<CS10); // CTC mode, compare max OCR1A
  TCNT1=0;
  TIMSK1|=(1<<OCIE1A); // enable compare interrupt timer 1
  sei();
  counter=0;
}
/******************************/

/**************GENERAL****************/
void end_job(void){
  PORTD&= ~(1<<CONVEYOR);
  PORTD&= ~(1<<PNEUMATIC);
  PORTB|=(1<<5);
  TCCR1B=0x00;
}
/******************************/

ISR(TIMER1_COMPA_vect){
  if(counter==(CONVEYOR_TIMER-1)){ // active for 10 seconds
    PORTD&= ~(1<<CONVEYOR);
    uart_puts("CONVEYOR OFF\n");
    uart_puts("PNEUMATIC ON\n");
    PORTD|=(1<<PNEUMATIC);
  }
  if(counter==((CONVEYOR_TIMER+PNEUMATIC_TIMER)-1)){ // active for 2 seconds
    PORTD&= ~(1<<PNEUMATIC);
    TCNT1=0;
    counter=0;
    uart_puts("PNEUMATIC OFF\n");
    TCCR1B=0x00;
  }

  counter++;
  /*itoa(counter,num2ch,10);
  uart_puts("TIMER = ");
  uart_puts(num2ch);
  uart_put('\n');*/
}

int main(){
  init_uart();
  DDRD|=(1<<CONVEYOR)|(1<<PNEUMATIC);
  DDRB|=(1<<5);
  PORTD|=(1<<SENSOR)|(1<<RESET);
  PORTD&= ~(1<<CONVEYOR)|(1<<PNEUMATIC);

  while(1){
    if(job<=10){
      if((PIND & (1<<SENSOR))==0){
        PORTB&= ~(1<<5);
        if(sensor!=1){
          uart_puts("\nCONVEYOR ON\n");
          PORTD|=(1<<CONVEYOR);
          init_timer1();
          job++;
        }
        sensor=1;
        itoa(job,num2ch,10);

        uart_puts("JOB = ");
        uart_puts(num2ch);
        uart_put('\n');
      }else if((PIND & (1<<SENSOR))!=0)
        sensor=0;
    }else{
      end_job();
      if((PIND & (1<<SENSOR))==0)
        uart_puts("JOB FINISHED! RESET TO RESTART.\n");
    }

    if((PIND & (1<<RESET))==0){
      job=0;
      end_job();

      itoa(job,num2ch,10);
      uart_puts("JOB = ");
      uart_puts(num2ch);
      uart_put('\n');
    }
    _delay_ms(150);
  }
}