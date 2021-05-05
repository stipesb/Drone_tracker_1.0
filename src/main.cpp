#include <Arduino.h>
#include <SMdriver.h>

vector_control konstrct;



int k1 = 500;// x os
int k2 = 500; // y os

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;




void setup() {
 konstrct.SetupZaBrojac();
 Serial.begin(115200);
 Serial.setTimeout(20);

}
void recvWithStartEndMarkers() {    // ne radi jos kako treba
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }


 if (newData == true)
   {
  
char brojX[33] = "";
char brojY[33] = "";
int t = 0;
int kt = 0;

for( int k = 0; k < 33; k++  )  // provjerava svaki element primljenog charasizeof(receivedChars)
{                                             
    if(receivedChars[k]!= ' ' && t == 0)   // ako naidje na razmak, prebacuje char na drugu varijablu
    {                                      
brojX[k] = receivedChars[k];               
    }
    else
    {
        t = 1;
    }
    
    if(t == 1 && receivedChars[k]!= ' ' )
    {
     brojY[kt] = receivedChars[k];
     kt++;
    }
      // ovaj kod gleda gdje je razmak u primljenom podatku, te ga u odnosu na taj razmak
      // dijeli na 2 chara, char prije razmaka i char posle razmaka


}

k1 = atoi(brojX);  // ova funkcija prebacuje char u integer
k2 = atoi(brojY);  // integer ide do +-32768  možda bude potreban veći format broja (long)
  newData = false;
  }

}


void loop() {
recvWithStartEndMarkers();
 
}



ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{
konstrct.tick(k2,k1);
}