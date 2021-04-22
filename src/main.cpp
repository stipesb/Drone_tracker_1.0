#include <Arduino.h>

int stepPin = 4;
int dirPin = 5;


void setup() {
  for(int i = 3; i<11; i++)
{
  pinMode(i,OUTPUT); 
}
digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(8,LOW);



}

void loop() {


  digitalWrite(dirPin,HIGH); 

  for(int x = 0; x < 5000; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(100); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100); 

  }
  delay(1000); 
  

  digitalWrite(dirPin,LOW); 
  for(int x = 0; x < 5000; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(100);
  }
  delay(1000);





}