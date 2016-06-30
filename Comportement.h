#ifndef Comportement_h
#define Comportement_h

#include "Arduino.h"

class Comportement {
    public:
        //initialize the sensor
        virtual void enter(Position aPosition) {
          positionInitiale=aPosition; 
          enterTime= millis();
        };
        unsigned long getEnterTime() {
          return enterTime;
        };
        Position getPositionInitiale() {
          return positionInitiale;
        };
        //read function must be implemented
        //this is called a pure virtual function
        virtual Position update() = 0;
        virtual Position exit() = 0;
    private:
        Position positionInitiale;
        //Position updatedPosition=Position();
        unsigned long enterTime;
};

#endif

