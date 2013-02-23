#ifndef _TRIANGLESTATIC_H_
#define _TRIANGLESTATIC_H_
#include "Point.h"
class Triangle;
//Clase triangulo estática, que sólo tiene los puntos y ninguna referencia
class TriangleStatic {
    public:
    Point p1;
    Point p2;
    Point p3;
    char triangletag;
    TriangleStatic() {this->triangletag = TriangleStatic::nextTag();} //constructor vacio 
    TriangleStatic(Point _p1, Point _p2, Point _p3) : p1(_p1), p2(_p2), p3(_p3) {this->triangletag = TriangleStatic::nextTag();}
    static TriangleStatic buildFromTriangle(Triangle T); //dado un Triangle, extrae sus puntos y retorna un triangulo estatico
    static char TAG;
    static char nextTag() {
        TriangleStatic::TAG++;
        return TriangleStatic::TAG;
    }
    bool operator ==(const TriangleStatic &compare_to);
    void print(bool enter = false);
    void draw();
};

#endif
