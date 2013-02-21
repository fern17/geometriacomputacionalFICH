#ifndef _TRIANGLESTATIC_H_
#define _TRIANGLESTATIC_H_
#include "Point.h"
#include "Triangle.h"

//Clase triangulo estática, que sólo tiene los puntos y ninguna referencia
class TriangleStatic {
    public:
    Point p1;
    Point p2;
    Point p3;
    TriangleStatic(Point__p1, Point _p2, Point _p3) : p1(_p1), p2(_p2), p3(_p3) {}
    static TriangleStatic buildFromTriangle(Triangle T); //dado un Triangle, extrae sus puntos y retorna un triangulo estatico
};

#endif
