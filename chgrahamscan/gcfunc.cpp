#include <cmath>
#include "Point2D.h"

#define EPS 0.000001


float modulo(Point2D & p1){
    return sqrt(p1.x*p1.x + p1.y*p1.y);
}

float dotProduct(Point2D & p1, Point2D & p2){
  return p1.x * p2.x + p1.y + p2.y;
}

//Retorna true si v1==v2 segun una tolerancia EPS definida arriba.
bool compareEqualFloat(float v1, float v2){
    return (std::abs(v1 - v2) < EPS);
}

//Devuelve el angulo en RADIANES entre dos Puntos
float anglePoint2D(Point2D & p1, Point2D & p2){
  float modp1 = modulo(p1);
  float modp2 = modulo(p2);
  float dotprod = dotProduct(p1,p2);
  float angle = std::acos(dotprod/(modp1*modp2));
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

