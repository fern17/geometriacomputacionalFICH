#include "Point2D.h"
#include <iostream>

extern bool compareEqualFloat(float, float);
extern bool comparePoint2DMinimalLeftDown(Point2D &, Point2D &);

Point2D::Point2D() {
}

Point2D::Point2D(float _x, float _y){
  x = _x;
  y = _y;
}

void Point2D::print(bool printCR){
  std::cout<<x<<' '<<y;
  if(printCR)
      std::cout<<std::endl;
  else
      std::cout<<" | ";
}

//Compara 2 puntos si sus coordenadas son iguales
bool Point2D::operator==(const Point2D &P) const{
  return (compareEqualFloat(x, P.x) and compareEqualFloat(y, P.y));
}
bool Point2D::operator<(Point2D P){
    return comparePoint2DMinimalLeftDown(*this, P);
}
Point2D  Point2D::operator-(Point2D P){
    Point2D retval;
    retval.x = x - P.x;
    retval.y = y - P.y;
    return retval;
}
