#include "Position.h"
#include "Comportement.h"
#include "Mouvement.cpp"

#include "Arduino.h"

class Arret : public Mouvement  {
    public:
        Arret (  ) : Mouvement ('g') {
        }
        virtual void enter(Position positionInitiale) {
          Comportement::enter(positionInitiale) ;
          getRightServo().write(90);;
          getLeftServo().write(90);;
        }
    protected:
        virtual Position getUpdatedPosition() {
          return getPositionInitiale();
        };
};

