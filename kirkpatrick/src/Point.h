#ifndef _POINT_H_
#define _POINT_H_
//Clase que representa un punto del plano.
class Point {
    static const float EPSILON = 0.0001;    //constante para las comparaciones de los operator== y operator!=
    public:
    float x;
    float y;
    Point();                            //constructor vacio
    Point(float _x, float _y);          //constructor por defecto
    bool operator ==(const Point &P);   //operador igual
    bool operator !=(const Point &P);   //operador distinto
    void print(bool enter = false);     //funcion que muestra el punto
    Point operator-(const Point &P) ;   //operador resta para calcular vectores
};

#endif
