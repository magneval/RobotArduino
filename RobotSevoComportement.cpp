
// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.

#include <avr/io.h>

#include <Arduino.h>
#include <Servo.h> 

#include "Position.h"
#include "Comportement.h"
#include "Arret.cpp"
#include "Avancer.cpp"
#include "Pivoter.cpp"
#include "Tourner.cpp"
#include "Encoder.cpp"

#include <avr/pgmspace.h>

#define time 1000
#define maxStep 5
#define maxLetter 0xF<<2
#define servoStep (180/maxStep)

static Mouvement* mouvements[]={
  new Arret(),
  new Avancer('t', 1),
  new Avancer('b', -1),
  new Pivoter('h', 1),
  new Pivoter('f', -1),
  new Tourner('r', 1, -1 ),
  new Tourner('v', -1, -1 ),
  new Tourner('n', -1, 1 ),
  new Tourner('y', 1, 1 )
};
Mouvement* mouvementCourrant;

//Comportement* comportements[]={ };
/*
char dirs[]={
  'g', //0
  't', //1
  'b', //10
  'x', //11
  'f', //100
  'r', //101
  'v', //110
  'x', //111
  'h', //1000
  'y', //1001
  'n', //1010
  'x', //1011
  'x', //1100&
  'x', //1101
  'x', //1110
  'x', //1111
  'G', //0
  'T', //1
  'B', //10
  'x', //11
  'F', //100
  'R', //101
  'V', //110
  'x', //111
  'H', //1000
  'Y', //1001
  'N', //1010
  'x', //1011
  'x', //1100&
  'x', //1101
  'x', //1110
  'x', //1111
 };
 */


//Servo rightServo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

//Servo leftServo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

//Servo headServo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  Serial.begin(9600);
  mouvementCourrant=mouvements[0];
  Position position= Position();
  mouvementCourrant->enter(position);
  /*
  headServo.attach(11);  // attaches the servo on pin 9 to the servo object 
   rightServo.attach(9);  // attaches the servo on pin 9 to the servo object 
   leftServo.attach(8);  // attaches the servo on pin 9 to the servo object 
   rightServo.write(90);              // tell servo to go to position in variable 'pos' 
   leftServo.write(90);              // tell servo to go to position in variable 'pos' 
   
   headServo.write(0);              // tell servo to go to position in variable 'pos' 
   delay(time);                       // waits 15ms for the servo to reach the position 
   headServo.write(90);              // tell servo to go to position in variable 'pos' 
   delay(time);                       // waits 15ms for the servo to reach the position 
   headServo.write(180);              // tell servo to go to position in variable 'pos' 
   delay(time);                       // waits 15ms for the servo to reach the position 
   */
  Serial.println("ready");

} 


void loop() 
{ 
 delay(100);
  Position position=mouvementCourrant->update();

  Serial.println(position.toJson());
  /*
  Serial.print("x = ");
  Serial.println(position.x);
  Serial.print("y = ");
  Serial.println(position.y);
  Serial.print("teta = ");
  Serial.println(position.teta);
  */
} 


void changeMouvement(char c) 
{ 
  Mouvement* mouvementPossible;
    byte p = 0; 
    byte mul=1;
    for (int i=0;i<sizeof(mouvements);i++){
      mouvementPossible=mouvements[i];
      if(c==mouvementPossible->getLetter()){
        Position position=mouvementCourrant->exit();
        //Serial.print("Change at ");
        Serial.println(position.toJson());
        mouvementCourrant= mouvements[i];
        mouvementCourrant->enter(position);
      }
    }

} 

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char c = (char)Serial.read();
    changeMouvement(c); 
  }
}




