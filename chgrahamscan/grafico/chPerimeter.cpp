#include <list>
#include "Point2D.h"
#include <iostream>
extern float dist(Point2D &, Point2D &);

//Devuelve la longitud del perimetro de un Convex Hull
float chPerimeter(std::list<Point2D> &Q){
    std::list<Point2D>::iterator p = Q.begin();
    std::list<Point2D>::iterator q = Q.begin();
    float distance = 0.0;
    q++;
    while(q != Q.end()){ //Calcula la distancia entre puntos adyacentes
        distance += dist(*p, *q);
        q++;
        p++;
    }
    distance += dist(*p, Q.front());//Calcula la distancia del ultimo con el primero
    return distance;
}

