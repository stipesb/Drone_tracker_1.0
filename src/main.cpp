#include <Arduino.h>
#include <SMdriver.h>




vector_control konstrct;



int k1 = 0;  // varijabla položaja objekta   X os
int k2 = 0;  // varijabla položaja objekta   Y os



const byte numChars = 32;    // varijable za primanje podataka na serijski port
char receivedChars[numChars];

boolean newData = false;




void setup() {
     


 konstrct.SetupZaBrojac();  // pozivanje funkcije za postavljanje tajmera i pinova
 Serial.begin(115200);      // pozivanje funkcije za serijsku komunikaciju
 Serial.setTimeout(20);     // vrijeme cekanja za primanje varijabli serijske komunikacije

}

void recvWithStartEndMarkers() {            // funkcija koja čita stringove koji su došli na serijski port
                                            // u obliku < pozicija_po_X_osi, pozicija_po_Y_osi>

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
                receivedChars[ndx] = '\0'; 
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

for( int k = 0; k < 33; k++  )          // provjerava svaki element primljenog "charasizeof(receivedChars)
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

k1 = atoi(brojX);  // prebacivanje chara u integer
k2 = atoi(brojY);  // integer ide do +-32768
  newData = false;
  }

}


void loop() {

recvWithStartEndMarkers();  //  prima broj poslan na serijski port,  u obliku <123, 366>

}



ISR(TIMER1_COMPA_vect)    //rutina koja se interruptom
                          //funkcije izmedju viticastih se poziva frekvencijom određenom
                          // usporednog registra, timer compare interrupt service routine
{
konstrct.tick(k2,k1);   
}