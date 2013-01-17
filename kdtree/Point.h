#ifndef POINT
#define POINT
#include <iostream>
#include <cmath>
class Point {
    public:
    static const float EPSILON = 0.00001;
    float x;
    float y;
    bool null;

    //constructor vacio
    Point() {
        this->x = -1;
        this->y = -1;
        this->null = true;
    }
    
    //Constructor por copia
    Point(const Point& P) {
        this->x = P.x;
        this->y = P.y;
        this->null = false;
    }

    //Constructor por parametros
    Point(float _x, float _y) : x(_x), y(_y), null(false) {}
    
    void print() { 
        if (not this->isNULL())
            std::cerr<<'('<<x<<','<<y<<')';
    }
    
    float operator[](const int idx){
        if (this->isNULL()) return -1;
        if (idx == 0) return x;
        else return y;
    }
    
    bool operator==(const Point &P) {
        if (this->isNULL()) 
            return false;
        else 
            return  (fabs(this->x - P.x) < this->EPSILON) and
                (fabs(this->y - P.y) < this->EPSILON);
    }

    bool isNULL() {
        return this->null == true;
    }
};
#endif
