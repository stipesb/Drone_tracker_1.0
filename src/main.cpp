#include <Arduino.h>
#include <tmc_vector_control.h>

vector_control konstrct;


int stepPin = 4;
int dirPin = 5;


//2
void setup() {
  /*
  for(int i = 3; i<11; i++)
{
  pinMode(i,OUTPUT); 
}
digitalWrite(9,HIGH);   //MS 1
digitalWrite(10,HIGH); //MS 2
digitalWrite(8,LOW);
digitalWrite(stepPin,LOW); 
  
    digitalWrite(dirPin,LOW); 
delay(10);
*/
 //dodatak
 konstrct.SetupZaBrojac();
}

void loop() {


delayMicroseconds(2000);
    digitalWrite(stepPin,HIGH);
delayMicroseconds(10);
     digitalWrite(stepPin,LOW);

  
} 


ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{
konstrct.tick();
}
