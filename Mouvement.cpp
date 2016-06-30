#ifndef Mouvement_h
#define Mouvement_h

#define  DISTANCE_MINUTE 10880
#define  LARGEUR 105

#include "Position.h"
#include "Comportement.h"
#include <Servo.h> 

#include "Arduino.h"

class Mouvement : public Comportement  {
  public:
    Mouvement(char aLetter) {
      letter=aLetter;
      rightServo.attach(9);  // attaches the servo on pin 9 to the servo object 
      leftServo.attach(8);  // attaches the servo on pin 9 to the servo object 
    }
    Servo getRightServo() {
      return rightServo;
    };
    Servo getLeftServo() {
      return leftServo;
    };
    char getLetter() {
      return letter;
    };
    int getVitesse() {
      return vitesse;
    };
    virtual Position update() {
      return getUpdatedPosition();
    };
    virtual Position exit() {
      return getUpdatedPosition();
    };
  protected:
    virtual Position getUpdatedPosition()=0;
  
  private:
    Servo rightServo;
    Servo leftServo;
    char letter;
    int vitesse=90;
};

#endif


