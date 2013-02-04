#ifndef _POINT_H_
#define _POINT_H_
#include <cmath>

class Point {
    static const float EPSILON = 0.000001;
    public:
    float x;
    float y;
    bool operator ==(const Point &P);
    bool operator !=(const Point &P);
    void print(bool enter = false);
    Point operator-(const Point &P) ;
};

#endif
