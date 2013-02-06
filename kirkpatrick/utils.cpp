#ifndef _UTILS_CPP_
#define _UTILS_CPP_

#include "Point.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

namespace utils{

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in intersection
// Comprobar si anda para segmentos
bool static getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &intersection) {
    Point s1;
    Point s2;
    s1.x = p1.x - p0.x;     s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;     s2.y = p3.y - p2.y;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        intersection.x = p0.x + (t * s1.x);
        intersection.y = p0.y + (t * s1.y);
        return true;
    }

    return false; // No collision
}

void loadPoints(std::string filename, std::vector<Point> &polygon) {
    std::ifstream file; 
    file.open(filename.c_str());
    if(!file.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<filename<<"\n";
        return;
    }
    
    std::cout<<"Leyendo puntos:\n";
    Point p;
    while (file>>p.x and file>>p.y) {
        p.print(true);
        polygon.push_back(p);
    }
    std::cout<<polygon.size()<<" puntos leidos\n";
    file.close();
}

float static dotProduct(const Point &v1, const Point &v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

float static crossProduct(const Point &v1, const Point &v2) {
    return v1.x*v2.y - v1.y*v2.x;
}

float static module(const Point &v) {
    return sqrt(pow(v.x, 2) + pow(v.y,2));
}

float static moduleSquared(const Point &v) {
    return (pow(v.x, 2) + pow(v.y,2));
}

float static angleBetweenVectors(const Point &v1, const Point &v2) {
    float dotP = dotProduct(v1, v2);
    float crossP = crossProduct(v1, v2);
    return atan(dotP/crossP);
}
//calcula el angulo angle(p1,p2,p3), donde p2 es el punto en comun
float static angleBetweenSegments(Point p1, Point p2, Point p3) {
    //Primero calculamos los vectores v1 y v2
    Point v1;
    Point v2;
    v1 = p1 - p2;
    v2 = p3 - p2;
    //Ahora calculamos el angulo teniendo los dos vectores
    return angleBetweenVectors(v1, v2);
}


//Retorna true si p1-p2 es el mismo segmento que p3-p4
bool sameSegment(Point &p1, Point &p2, Point &p3, Point &p4)  {
    if (p1 == p3 and p2 == p4)
        return true;
    if (p1 == p4 and p2 == p3)
        return true;
    else
        return false;
}

//Retorna true si p1-p2 es el mismo segmento que p3-p4, pero hace comparacion de indices no mas
bool sameSegment(const int p1, const int p2, const int p3, const int p4) {
    if (p1 == -1 or p2 == -1 or p3 == -1 or p4 == -1) //puntos no encontrados
        return false;
    if (p1 == p3 and p2 == p4)
        return true;
    if (p1 == p4 and p2 == p3)
        return true;
    else
        return false;
}

//Dada una lista de puntos en CCW y 2 puntos p1,p2. 
//Retorna true si se puede agregar una diagonal.
//False si no se puede agregar una diagonal entre p1 y p2
//Una diagonal se puede agregar si y solo si:
// I) No intersecta a ningun segmento del poligno
// II) Es interna al poligono
bool diagonalInsidePolygon(std::vector<Point> polygon, const Point p1, const Point p2) {
    if (polygon.size() <= 3) //Poligono muy chico, imposible agregar diagonal
        return false;
     
    //Primero vamos a encontrar los indices de p1 y p2 dentro de polygon
    //Los inicializamos con not_found primero
    int index_p1 = -1; //indice de p1 dentro de polygon
    int index_p2 = -1; //indice de p2 dentro de polygon
    for (unsigned int i = 0; i < polygon.size(); i++) {
        //actualizamos los indices si es que los encontramos y no los habiamos encontrado ya
        if (index_p1 == -1 and polygon[i] == p1) 
            index_p1 = i;
        if (index_p2 == -1 and polygon[i] == p2) 
            index_p2 = i;
    }

    //Recorremos cada segmento (polygon[i]-polygon[i+1]
    for (unsigned int i = 0; i < polygon.size()-1; i++) {
        //if (sameSegment(p1, p2, polygon[i], polygon[i+1])) continue;
        //si son el mismo segmento, no hago nada
        if (sameSegment(index_p1, index_p2, i, i+1))
            continue;
        else {
            //Si la linea p1-p2 se intersecta con p_i-p_(i+1) => no es una diagonal valida
            Point phantom;
            if (getLineIntersection(p1, p2, polygon[i], polygon[i+1], phantom))
                return false;
        }
    }
    //ultimo con el primero
    //if (sameSegment(p1, p2, polygon.back(), polygon.front())) return false;
    if (sameSegment(index_p1, index_p2, polygon.size()-1, 0))
        return false;
    else { 
        Point phantom; //punto que no se usa para nada
        if (getLineIntersection(p1, p2, polygon.back(), polygon.front(), phantom))
            return false;
    }
    
    //Hasta aquí, sabemos que la diagonal p1-p2 no se intersecta con ningun segmento del poligono
    //Ahora dejamos en index_p1 el indice menor. Si la diagonal estaba al reves
    //(el indice del primer punto es mayor que el segundo), hay que intercambiar
    if (index_p1 > index_p2) {
        int temp = index_p1;
        index_p1 = index_p2;
        index_p2 = temp;
    }
    unsigned int index_to_use = index_p1 + 1;
    if (index_to_use >= polygon.size())//index_p1 es justo el ultimo del poligono
        index_to_use = 0;//usamos el primero entonces
    
    //Ahora debemos comprobar que es interna
    //
    //Calculamos el angulo entre p1-p2 y p1-v_i. Notar que p1 es el pivote y por eso va en el medio
    float angle = angleBetweenSegments(polygon[index_to_use], p1, p2); 

    //Si el angulo entre p1-p2 y el segmento p_i-pi+1 con p_i = p1 es positivo => diagonal externa
    if (angle > 0)
        return false;
    else
        return true;
}



};

#endif
