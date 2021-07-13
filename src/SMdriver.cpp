#include "SMdriver.h"

/*  Biblioteka SMdriver koja kontrolira brzinu rotacije 3 koračna motora 

 Driver sadrži 3xTMC2208 drivera, arduino nano i regulator napona 

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


int a = 0;      // varijabla a
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
  OCR1A = 800;          // frekvencija interrupta 20kHz  50us,      (za svakih 20us  OCF1A = 319)
             // formula za usporedni registar = [ 16,000,000Hz/ (prescaler * željena frekvencija interupta) ] - 1
  TCCR1B |= (1 << WGM12);   // CTC mode

 // TCCR1B |= ((1 << CS12) | (1 << CS10));  //1024 prescaler
  
  TCCR1B |= (1 << CS10);    // prescaler = 1, velika frekvencija timera
  TIMSK1 |= (1 << OCIE1A);  // aktivira interupte usporednog registra
  interrupts();             // aktivira interupte



}
void vector_control::klik(){

}


void vector_control::tick(int brzina_y, int brzina_x)  // ova funkcija se poziva svakih 50us                 
{  

if(brzina_x >0)
{
digitalWrite(Driver2Dir,HIGH);  // postavlja dir pin u high ili low, ovisno u koju stranu ce se okretati motor
}
else
{
digitalWrite(Driver2Dir,LOW);   // prebacuje brzinu na pozitivan predznak, radi daljnjih funkcija
brzina_x = -brzina_x;

}



if(brzina_y >0)
{
digitalWrite(Driver1Dir,LOW);  // postavlja dir pin u high ili low, ovisno u koju stranu ce se okretati motor
}
else
{
digitalWrite(Driver1Dir,HIGH);
brzina_y = -brzina_y;              // prebacuje brzinu na pozitivan predznak, radi daljnjih funkcija
}



if(brzina_x<100) // // fuzzy + proporcionalni regulator sa 3 zone za os lijevo/desno
{

brzina_x = 10000 - brzina_x*50;

}
else if(brzina_x<220)
{
  brzina_x = 5000 - brzina_x*20;
}
else if(brzina_x>220)
{
  brzina_x = 500;
}





if(brzina_y<100)  // fuzzy + proporcionalni regulator sa 3 zone za os gore/dolje
{

brzina_y = 10000 - brzina_y*50;

}
else if(brzina_y<180)
{
  brzina_y = 5000 - brzina_y*20;
}
else if(brzina_y>180)
{
  brzina_y = 500;
}




  digitalWrite(Driver1Step,LOW);
 
  digitalWrite(Driver2Step,LOW);
 


if(brzina_x<9000)   // ovaj uvjet zaustavlja manipulator kada se dron nalazi
{                   // unutar mrtve zone.

timerx = timerx+50;            // inkrement tajmera

if(timerx>brzina_x)            //provjera uvjeta koliko je prošlo vremena od posljednjeg impulsa
{
digitalWrite(Driver2Step,HIGH);  // postavljanje impulsa na step pin

timerx = 0;                      // nuliranje tajmera za ponovno inkrementiranje
}
}



if(brzina_y<9000)  // (fuzzy regulator) ovo radi mrtvu zonu kad je dron centriran  
                   //npr ako je dron 15 pixela oko y osi, i ako uracunamo gain
                   // tako dobijemo racunicu 10000 - 15*50  rezultat je 9250, 
                   //   sa tim rezultatom if uvjet nije zadovoljen i gimbal ce zaustaviti gibanje
{

timery = timery+50;

if(timery>brzina_y)
{
digitalWrite(Driver1Step,HIGH);
timery = 0;
}

}





}






void vector_control::test()  // ova funkcija samo pokrene motore da se vidi njihov rad
{
   digitalWrite(Driver1Dir,HIGH);
 digitalWrite(Driver2Dir,HIGH);
 digitalWrite(Driver3Dir,HIGH);
 for(int x = 0; x < 2000; x++) {
delayMicroseconds(1000);
    digitalWrite(Driver1Step,HIGH);
     digitalWrite(Driver2Step,HIGH);
     digitalWrite(Driver3Step,HIGH);
delayMicroseconds(100);
digitalWrite(Driver3Step,LOW);
     digitalWrite(Driver1Step,LOW);
     digitalWrite(Driver2Step,LOW);
       
 }

    digitalWrite(Driver1Dir,LOW);
 digitalWrite(Driver2Dir,LOW);
 digitalWrite(Driver3Dir,LOW);
 for(int x = 0; x < 2000; x++) {
delayMicroseconds(1000);
    digitalWrite(Driver1Step,HIGH);
     digitalWrite(Driver2Step,HIGH);
      digitalWrite(Driver3Step,HIGH);
delayMicroseconds(10);
     digitalWrite(Driver1Step,LOW);
     digitalWrite(Driver2Step,LOW);
     digitalWrite(Driver3Step,LOW);
 }

}