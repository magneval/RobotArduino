#include "Position.h"
#include "Comportement.h"
#include "Mouvement.cpp"

#include "Arduino.h"

class Avancer : public Mouvement  {
    public:
      Avancer (char letter,int direction ) :
      Mouvement (letter)        {  
        sens=direction;
      }
      virtual void enter(Position positionInitiale) {
        Comportement::enter(positionInitiale) ;
        getRightServo().write(right);
        getLeftServo().write(left);
        updatedPosition.teta=positionInitiale.teta;
      }
   protected:
      virtual Position getUpdatedPosition() {
        long xi=getPositionInitiale().x;
        long yi=getPositionInitiale().y;
        float teta=getPositionInitiale().teta;
        long updateTime =millis();
        long enterTime =getEnterTime();
        float distance=DISTANCE_MINUTE*(updateTime-enterTime)/60000;
        updatedPosition.x=xi+distance*cos(teta)*sens;
        updatedPosition.y=yi+distance*sin(teta)*sens;
        return updatedPosition;
      };
   private:
      Position updatedPosition=Position();
      int sens=1;
      byte right=90-getVitesse()*sens;
      byte left=90+getVitesse()*sens;
};


