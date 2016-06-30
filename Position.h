#ifndef Position_h
#define Position_h

#include <Arduino.h>
#include <stdlib.h>

class Position {
public:
  long x = 0;
  long y = 0;
  float teta = 0;
  virtual String toJson(){

    long tetaInt=(int) teta;
    long tetaDec=long(teta*10000) % 10000;
    char tetaJson[20];
    dtostrf(teta,20,5,tetaJson);
    return String("{'x':")+x+String("',y':")+y+String(",'teta':")+tetaJson+String("'}");
    /*
          char json[255];
     sprintf(json,"{'x':%d',y':%d,'teta':%d'}" ,x,y,teta);
     //          return String("{'x':")+x+String("',y':")+y+String(",'teta':")+teta+String("'}");
     return json;
     */
  };
};

#endif


