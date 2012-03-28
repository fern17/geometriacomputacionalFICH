#ifndef __POINT2D_H__
#define __POINT2D_H__

#include <iostream>
extern bool compareEqualFloat(float, float);

class Point2D{
public:
  float x;
  float y;
  Point2D() {}
  Point2D(float _x, float _y){
    x = _x;
    y = _y;
  }

  void print(){
    std::cout<<x<<' '<<y<<std::endl;
  }

  //Compara 2 puntos si sus coordenadas son iguales
  bool operator==(Point2D P){
    return (compareEqualFloat(x, P.x) and compareEqualFloat(y, P.y));
  }
};


#endif

