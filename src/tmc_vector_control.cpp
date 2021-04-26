#include "tmc_vector_control.h"
int a = 0;
int timer = 0;
//////////////////////////////////////
vector_control::vector_control(){
}
vector_control::~vector_control(){
}
void vector_control::SetupZaBrojac(){     

  for(int i = 3; i<11; i++)  // postavljanje pinova 3-10 kao output
{
  pinMode(i,OUTPUT); 
  delay(5);
  digitalWrite(i,LOW);
}

digitalWrite(9,HIGH);   //MS 1 pin
digitalWrite(10,HIGH); //MS 2  pin
digitalWrite(8,LOW);   // EN pin, (low) za aktivirat driver (HIGH) za deaktivirat driver


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

}//tt
