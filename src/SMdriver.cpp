#include "SMdriver.h"
/*  Biblioteka za drive SMdriver za pokretanje 3 x stepper motora.

 Driver sadrži 3xTMC2208 drivera, arduino nano, regulator napona i zaštitu od obrnutog
smjera struje
*/
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
int timerx = 0;
int timery = 0;
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
  OCR1A = 800;            // frekvencija interrupta 50kHz, svakih 20us   319
                             //compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
  TCCR1B |= (1 << WGM12);   // CTC mode
 // TCCR1B |= ((1 << CS12) | (1 << CS10));  //1024 prescaler
  
  TCCR1B |= (1 << CS10);  // prescaler = 1, velika frekvencija timera
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts


  
  
}
void vector_control::klik(){

}


void vector_control::tick(int brzina_x, int brzina_y)
{
if(brzina_x >0)
{
digitalWrite(Driver1Dir,LOW);
}
else
{
digitalWrite(Driver1Dir,HIGH);
brzina_x = -brzina_x;
}
if(brzina_y >0)
{
digitalWrite(Driver2Dir,HIGH);
}
else
{
digitalWrite(Driver2Dir,LOW);
brzina_y = -brzina_y;
}

brzina_x = 6500 - brzina_x*10;
brzina_y = 6500 - brzina_y*6;


if(digitalRead(Driver1Step))
{
  digitalWrite(Driver1Step,LOW);
 }
if(digitalRead(Driver2Step))
{
  digitalWrite(Driver2Step,LOW);
 }




timerx = timerx+20;

if(timerx>brzina_x)
{
digitalWrite(Driver1Step,HIGH);
timerx = 0;
}

timery = timery+20;

if(timery>brzina_y)
{
digitalWrite(Driver2Step,HIGH);
timery = 0;
}



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