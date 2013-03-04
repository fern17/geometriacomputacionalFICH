#ifndef _TRIANGLESTATIC_H_
#define _TRIANGLESTATIC_H_
#include "Point.h"
//Declaracion por adelantado
class Triangle;

//Clase triangulo estática, que sólo tiene los puntos y ninguna referencia
class TriangleStatic {
    public:
    //Puntos de este triangulo
    Point p1;
    Point p2;
    Point p3;
    unsigned int triangletag;           //Tag para identificar el triangulo

    TriangleStatic();                   //constructor vacio que le asigna un tag 
    TriangleStatic(Point _p1, Point _p2, Point _p3);    //constructor con puntos. Le asigna un tag
    bool operator ==(const TriangleStatic &compare_to); //True si representan el mismo triangulo
    void print(bool enter = false);     //Muestra el triangulo en la salida estandar
    void draw();                        //Opengl

    static TriangleStatic buildFromTriangle(Triangle T); //dado un Triangle, extrae sus puntos y retorna un triangulo estatico

    //Metodos estaticos para la generacion de TAGS
    static unsigned int TAG;
    static unsigned int nextTag() {
        TriangleStatic::TAG++;
        return TriangleStatic::TAG;
    }
};

#endif
