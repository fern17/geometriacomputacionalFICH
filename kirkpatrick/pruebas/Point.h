#ifndef _POINT_H_
#define _POINT_H_

class Point {
    static const float EPSILON = 0.0001;
    public:
    Point();
    Point(float _x, float _y);
    float x;
    float y;
    bool operator ==(const Point &P);
    bool operator !=(const Point &P);
    void print(bool enter = false);
    Point operator-(const Point &P) ;
};

#endif
