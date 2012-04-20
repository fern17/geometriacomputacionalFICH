#include <cmath>
#include "Point2D.h"
#include "Point3D.h"

#define EPS 0.000001

//Retorna true si v1==v2 segun una tolerancia EPS definida arriba.
bool compareEqualFloat(float v1, float v2){
    return (std::abs(v1 - v2) < EPS);
}

//Devuelve la distancia entre dos puntos
float dist(Point2D &p1, Point2D &p2){
    float dx = p1.x - p2.x;
    float dy = p1.y - p2.y;
    float distance = sqrt(dx*dx + dy*dy);
    return distance;
}

//Devuelve el modulo de un Punto en 2d
float modulo(Point2D & p1){
    return sqrt(p1.x*p1.x + p1.y*p1.y);
}

//Devuelve el modulo de un Punto en 3d
float modulo(Point3D & p1){
    return sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);
}

//Devuelve la distancia perpendicular entre dos rectas paralelas
//x1, y1 : punto de la primer recta
//a2, b2, c2: parametros de la ecuacion de la segunda recta: ax + by = c
float perpDist(float x1, float y1, float a2, float b2, float c2){
    float t1 = std::abs(a2*x1 + b2*y1 + c2);
    float t2 = std::sqrt(a2*a2 + b2*b2);
    if(compareEqualFloat(t2,0.0))
        return t1;
    else
        return t1/t2;
}

//Calcula el producto punto entre dos puntos en el plano
float dotProduct(Point2D & p1, Point2D & p2){
  return p1.x*p2.x + p1.y*p2.y;
}
//Calcula el producto punto entre dos puntos en el espacio
float dotProduct(Point3D & p1, Point3D & p2){
  return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

//Calcula el producto Vectorial entre dos puntos en el espacio
Point3D crossProduct(Point3D & p1, Point3D & p2){
    Point3D retval;
    retval.x = p1.y*p2.z - p1.z*p2.y;
    retval.y = -(p1.x*p2.z - p1.z*p2.x);
    retval.z = p1.x*p2.y - p1.y*p2.x;
    return retval;
}

//Computa la coordenada Z del vector resultado, que es lo que interesa
float crossProduct(Point2D & p1, Point2D & p2){
    float retval = p1.x*p2.y - p1.y*p2.x;
    return retval;
}


//Devuelve el angulo en RADIANES entre dos Puntos
float anglePoint2D(Point2D & p1, Point2D & p2, bool comparar = true){
  float modp1 = modulo(p1);
  float modp2 = modulo(p2);
  float angle = 0.0;

  if( (comparar == true) && (compareEqualFloat(modp1, modp2) == false) ){ 
      return angle; //retorna 0.0 porque son coincidentes
  }

  if(compareEqualFloat(modp1,0)){ //modulo 0 del primero
      angle = std::acos(p2.y/modp2);
  } 
  else if (compareEqualFloat(modp2,0)){ //modulo 0 del segundo
    angle = std::acos(p1.y/modp1);
  }
  else {
    float dotprod = dotProduct(p1,p2);
    angle = std::acos(dotprod/(modp1*modp2));
  } 
  
  
  return angle;
}

//Retorna el area con signo del triangulo p1,p2, p3
float signedArea(Point2D &p1, Point2D &p2, Point2D &p3){
  float det = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
  return det;
}

//Retorna true si p1, p2 y p3 forman un giro a la izquierda
bool leftTurn(Point2D &p1, Point2D &p2, Point2D &p3){
  return (signedArea(p1, p2, p3) > 0);
}

//Retorna true si P1 esta mas abajo de P2. 
// Si estan iguales (segun un EPS definido arriba), retorna true si la x de P1 es menor que la de P2. 
// Si no, devuelve false.
bool comparePoint2DMinimalLeftDown(Point2D & p1, Point2D & p2){
  if(p1.y < p2.y) return true;
  else if(compareEqualFloat(p1.y, p2.y) and (p1.x < p2.x)) return true;
  else return false;
}

