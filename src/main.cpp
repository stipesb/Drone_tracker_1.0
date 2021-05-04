#include <Arduino.h>
#include <SMdriver.h>

vector_control konstrct;


int c = 2000;  // x os
int b = 2000;  // y os

const byte numChars = 32;
char receivedChars[numChars];

boolean newData = false;


void setup() {
 konstrct.SetupZaBrojac();
 Serial.begin(9600);
 Serial.setTimeout(10);

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
}

void showNewData() {
    if (newData == true) {
        Serial.println(receivedChars);
        newData = false;
    }
}
void loop() {
recvWithStartEndMarkers();
    showNewData();

    if(receivedChars[2] == 'w')
    {
digitalWrite(LED_BUILTIN,HIGH);
    }
}









ISR(TIMER1_COMPA_vect)    //rutina koja poziva timer da pozove funkcije izmedju viticastih zagrada svako onoliko vremena koji je određen prescalerima      
                          // timer compare interrupt service routine
{
konstrct.tick(b,c);
}
