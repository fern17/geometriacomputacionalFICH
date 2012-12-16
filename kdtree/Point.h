#ifndef POINT
#define POINT
#include <iostream>
class Point {
    public:
    float x;
    float y;
    Point(float _x, float _y) : x(_x), y(_y) {}
    void print() { std::cerr<<'('<<x<<','<<y<<')'; }
    float & operator[](const int idx){
        if (idx == 0) return x;
        else return y;
    }
};
#endif
