#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
//Declaracion por adelantado
class Vertex;
//Clase que representa un triangulo del grafo plano
class Triangle {
    public:
    //Los 3 vertices que definen a este triangulo
    Vertex *p1;
    Vertex *p2;
    Vertex *p3;

    Triangle(Vertex *_p1, Vertex * _p2, Vertex *_p3) : p1(_p1), p2(_p2), p3(_p3) {} //constructor
    void print(bool enter = false);         //Imprime en la salida estandar
    bool isSegment(Vertex *v1, Vertex *v2); //True si v1 y v2 forman una arista de este triangulo
    void deleteAllPoints();                 //Borra la referencia de los puntos a este triangulo

    void draw();                            //Opengl
};

#endif
