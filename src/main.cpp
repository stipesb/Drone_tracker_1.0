#include <Arduino.h>
#include <SMdriver.h>

vector_control konstrct;


void setup() {
  
 konstrct.SetupZaBrojac();
}

void loop() {

konstrct.test();

delay(4000);

  
} 


ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{

}

