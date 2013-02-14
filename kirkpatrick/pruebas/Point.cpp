#include "Point.h"
#include <iostream>
#include <cmath> 

//Constructor vacio, no hace nada
Point::Point() { }

Point::Point(float _x, float _y) {
    this->x = _x;
    this->y = _y;
}

bool Point::operator ==(const Point &P) {
    return ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

bool Point::operator !=(const Point &P) {
    return not ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

Point Point::operator -(const Point &P) {
    Point ret_val;
    ret_val.x = this->x - P.x;
    ret_val.y = this->y - P.y;
    return ret_val;
}
void Point::print(bool enter) {
    std::cout<<"("<<x<<", "<<y<<")";
    if (enter)
        std::cout<<"\n";
}
