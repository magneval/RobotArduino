#include "Position.h"
#include "Comportement.h"
#include "Mouvement.cpp"

#include "Arduino.h"

class Pivoter : public Mouvement  {
    public:
      Pivoter (char letter,int direction ) :
      Mouvement (letter)        {  
        sens=direction;
      }
      virtual void enter(Position positionInitiale) {
              Comportement::enter(positionInitiale) ;
        getRightServo().write(right);
        getLeftServo().write(left);
        updatedPosition.x=positionInitiale.x;
        updatedPosition.y=positionInitiale.y;
      }
    protected:
      virtual Position getUpdatedPosition() {
        float teta=getPositionInitiale().teta;
        long updateTime =millis();
        long enterTime =getEnterTime();
        float distance=DISTANCE_MINUTE*(updateTime-enterTime)/60000;
        updatedPosition.teta=teta-2*distance/LARGEUR*sens;
        return updatedPosition;
      };
    private:
      Position updatedPosition=Position();
      int sens=1;
      byte right=90+getVitesse()*sens;
      byte left=90+getVitesse()*sens;
};


