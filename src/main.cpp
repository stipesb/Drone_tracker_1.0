#include <Arduino.h>
#include <SMdriver.h>

vector_control konstrct;


void setup() {
  
 konstrct.SetupZaBrojac();
}

void loop() {


String a = Serial.readString();

//ovde ide konverzija iz stringa u int x i int y

int b =2;
int c = 3;


konstrct.tick(b,c);



konstrct.test();

delay(4000);

  





} 






ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{

}

