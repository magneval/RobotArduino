#include "Position.h"
#include "Comportement.h"
#include "Mouvement.cpp"
#include <math.h>
#define pi atan(1)*4

#include "Arduino.h"

class Tourner : public Mouvement  {
    public:
      Tourner (char letter,int avArr,int droiteGauche ) :
      Mouvement (letter)        {  
        sens=avArr;
        orientation=droiteGauche;
      }
      virtual void enter(Position positionInitiale) {
              Comportement::enter(positionInitiale) ;
        getRightServo().write(right);
        getLeftServo().write(left);
        pivotPosition.x=positionInitiale.x+LARGEUR/2*sin(positionInitiale.teta)*orientation;
        pivotPosition.y=positionInitiale.y-LARGEUR/2*cos(positionInitiale.teta)*orientation;
        pivotPosition.teta=positionInitiale.teta;
  Serial.print("pivotPosition = ");
  Serial.println(pivotPosition.toJson());
      }
    protected:
      virtual Position getUpdatedPosition() {
        float teta=getPositionInitiale().teta;
        long updateTime =millis();
        long enterTime =getEnterTime();
        float distance=DISTANCE_MINUTE*(updateTime-enterTime)/60000;
        //                  MOD(R2;R$1*2)-(R$1)
        updatedPosition.teta=fmod(teta-distance/LARGEUR*sens*orientation,pi*2)-pi;
        //                  X_Pivot      -LARGEUR/2*SIN(R15)*droiteGauche
        updatedPosition.x=pivotPosition.x-LARGEUR/2*sin(updatedPosition.teta)*orientation;
        //                  Y_Pivot      +LARGEUR/2*COS(R3)*droiteGauche
        updatedPosition.y=pivotPosition.y+LARGEUR/2*cos(updatedPosition.teta)*orientation;
        return updatedPosition;
      };
    private:
      Position pivotPosition=Position();
      Position updatedPosition=Position();
      int sens=1;
      int orientation=1;

/*
int rights[]={    sens  orientation
  1,//'\', //101     1    -1
  -1,//'/', //110   -1    -1
  0,//'/', //1001    1     1
  0,//'\', //1010   -1     1
  =
 */
      byte right=90-getVitesse()*(1-orientation)/2*sens;

/*
int lefts[]={     sens  orientation
  0,//'\', //101     1    -1 
  0,//'/', //110    -1    -1
  1,//'/', //1001    1     1
  -1,//'\', //1010  -1     1
  = (orientation +1/2)
 */
      byte left=90+getVitesse()*(1+orientation)/2*sens;

      /*
      * tout droit
      byte right=90-getVitesse()*sens;
      byte left=90+getVitesse()*sens;
      */
      /*
      * pivoter
      byte right=90+getVitesse()*avArr;
      byte left=90+getVitesse()*avArr;
      */
};


