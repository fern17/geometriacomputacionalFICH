#include "Point.h"
#include <iostream>
#include <cmath> 

//Constructor vacio, no hace nada
Point::Point() { }

//Constructor por defecto
Point::Point(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

//True si this y P tienen las mismas coordenadas
bool Point::operator ==(const Point &P) {
    return ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

//True si this y P no tienen las mismas coordenadas
bool Point::operator !=(const Point &P) {
    return not ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

//Devuelve la resta de this y P (para usarlo como vector
Point Point::operator -(const Point &P) {
    Point ret_val;
    ret_val.x = x - P.x;
    ret_val.y = y - P.y;
    return ret_val;
}

//Imprime el punto por la salida estandar
void Point::print(bool enter) {
    std::cout<<"("<<x<<", "<<y<<")";
    if (enter)                      //retorno de carro
        std::cout<<"\n";
}
