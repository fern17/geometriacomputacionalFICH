#include "Point2D.h"
#include <iostream>
extern bool compareEqualFloat(float, float);

Point2D::Point2D() {
}

Point2D::Point2D(float _x, float _y){
  x = _x;
  y = _y;
}

void Point2D::print(){
  std::cout<<x<<' '<<y<<std::endl;
}

//Compara 2 puntos si sus coordenadas son iguales
bool Point2D::operator==(Point2D P){
  return (compareEqualFloat(x, P.x) and compareEqualFloat(y, P.y));
}
