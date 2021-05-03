#include <Arduino.h>
#include <SMdriver.h>

vector_control konstrct;


const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;


int b = 500;
int c = 500;

void setup() {
  
 konstrct.SetupZaBrojac();
}

void loop() {


//usbPrijem();


//ovde ide konverzija iz stringa u int x i int y





} 

void usbPrijem()
{

    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }

}

void stringToInt()
{
if(newData == true)
{
    char t[10];
    char f[10];
     char k = ' ';

for(int i = 0; i>sizeof(receivedChars)  ;   i++   )
{
 
 if(receivedChars[i] != ' ')
 t[i] = receivedChars[i];
 else
 f[i]=receivedChars[i];
}

b = atoi(t);
c = atoi(f);

}



}






ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{
konstrct.tick(b,c);
    

}

