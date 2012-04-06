#include "Point3D.h"
#include <iostream>

extern bool compareEqualFloat(float, float);

Point3D::Point3D() {
}
Point3D(Point2D P){
    x = P.x;
    y = P.y;
    z = 0;
}

Point3D::Point3D(float _x, float _y, float _z){
  x = _x;
  y = _y;
  z = _z;
}

void Point3D::print(){
  std::cout<<x<<' '<<y<<' '<<z<<' 'std::endl;
}

//Compara 2 puntos si sus coordenadas son iguales
bool Point2D::operator==(Point3D P){
  return (compareEqualFloat(x, P.x) and compareEqualFloat(y, P.y) and compareEqualFloat(z, P.z));
}

Point3D  Point3D::operator-(Point3D P){
    Point3D retval;
    retval.x = x - P.x;
    retval.y = y - P.y;
    retval.z = z - P.z;
return retval;
}
