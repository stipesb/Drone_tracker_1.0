#include "tmc_vector_control.h"
// definiranje pinova stepper modula
#define Driver1Dir 4
#define Driver1Step 5

#define Driver2Dir 6
#define Driver2Step 7

#define Driver3Dir 8
#define Driver3Step 9

#define MS1 2
#define MS2 3


int a = 0;
int timer = 0;
//////////////////////////////////////
vector_control::vector_control(){
}
vector_control::~vector_control(){
}
void vector_control::SetupZaBrojac(){     

  for(int i = 2; i<10; i++)  // postavljanje pinova 3-10 kao output
{
  pinMode(i,OUTPUT); 
  delay(5);
  digitalWrite(i,LOW);
}

digitalWrite(MS1,HIGH);   //MS 1 pin
digitalWrite(MS2,HIGH); //MS 2  pin

delay(10);


  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;            // compare match register 16MHz/(256/2Hz)
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= ((1 << CS12) | (1 << CS10));  //1024 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}
void vector_control::klik(){

}
void vector_control::tick(){

}

void vector_control::test()
{
   digitalWrite(Driver1Dir,HIGH);
 digitalWrite(Driver2Dir,HIGH);
 digitalWrite(Driver3Dir,HIGH);
 for(int x = 0; x < 2000; x++) {
delayMicroseconds(2000);
    digitalWrite(Driver1Step,HIGH);
     digitalWrite(Driver2Step,HIGH);
     digitalWrite(Driver3Step,HIGH);
delayMicroseconds(10);
digitalWrite(Driver3Step,LOW);
     digitalWrite(Driver1Step,LOW);
     digitalWrite(Driver2Step,LOW);
 }

    digitalWrite(Driver1Dir,LOW);
 digitalWrite(Driver2Dir,LOW);
 digitalWrite(Driver3Dir,LOW);
 for(int x = 0; x < 2000; x++) {
delayMicroseconds(2000);
    digitalWrite(Driver1Step,HIGH);
     digitalWrite(Driver2Step,HIGH);
      digitalWrite(Driver3Step,HIGH);
delayMicroseconds(10);
     digitalWrite(Driver1Step,LOW);
     digitalWrite(Driver2Step,LOW);
     digitalWrite(Driver3Step,LOW);
 }

}