#ifndef _UTILS_CPP_
#define _UTILS_CPP_
#include "Vertex.h"
#include "Point.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

namespace utils{

const static float RADIAN = 180/M_PI;

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in intersection
bool static getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &intersection, bool lessequal = true) {
    Point s1;
    Point s2;
    s1.x = p1.x - p0.x;     s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;     s2.y = p3.y - p2.y;

    float s, t;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / (-s2.x * s1.y + s1.x * s2.y);

    //Lo siguiente depende del comparador que se use, menor/mayor o menor/mayor igual
    bool colission = false;
    if (lessequal) { //menorigual/mayorigual
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
            colission = true;
    }
    else { //mayor/menor solo
        if (s > 0 && s < 1 && t > 0 && t < 1)
            colission = true;
    }
    if (colission) {
        // Collision detected
        intersection.x = p0.x + (t * s1.x);
        intersection.y = p0.y + (t * s1.y);
        return true;
    }

    return false; // No collision
}

void static loadPoints(std::string filename, std::vector<Point> &polygon) {
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

float static dist(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

float static angleVectors(Point &v1, Point &v2) {
    Point res = v2-v1;
    float angle = atan2(res.y,res.x) * RADIAN;
    if (angle < 0)
        angle = angle+360;
    return angle;
}

float static angleBetweenVectors(const Point &v1, const Point &v2) {
    return (atan2(v2.y,v2.x) - atan2(v1.y,v1.x))*RADIAN;
    /*
    float dotP = dotProduct(v1, v2);
    float crossP = crossProduct(v1, v2);
    return atan(dotP/crossP);
    */
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

/*  
//Retorna true si p1-p2 es el mismo segmento que p3-p4
bool static sameSegment(Point &p1, Point &p2, Point &p3, Point &p4)  {
    if (p1 == p3 and p2 == p4)
        return true;
    if (p1 == p4 and p2 == p3)
        return true;
    else
        return false;
}

//Retorna true si p1-p2 es el mismo segmento que p3-p4, pero hace comparacion de indices no mas
bool static sameSegment(const int p1, const int p2, const int p3, const int p4) {
    if (p1 == -1 or p2 == -1 or p3 == -1 or p4 == -1) //puntos no encontrados
        return false;
    if (p1 == p3 and p2 == p4)
        return true;
    if (p1 == p4 and p2 == p3)
        return true;
    else
        return false;
}
*/

//Dada una lista de puntos en CCW y 2 puntos p1,p2. 
//Retorna true si se puede agregar una diagonal.
//False si no se puede agregar una diagonal entre p1 y p2
//Una diagonal se puede agregar si y solo si:
// I) No intersecta a ningun segmento del poligno
// II) Es interna al poligono
bool static diagonalInsidePolygon(std::vector<Vertex *> polygon, unsigned int index_p1, unsigned int index_p2) {
    if (polygon.size() <= 3) //Poligono muy chico, imposible agregar diagonal
        return false;
     
        
    //Ahora dejamos en index_p1 el indice menor. Si la diagonal estaba al reves
    //(el indice del primer punto es mayor que el segundo), hay que intercambiar
    if (index_p1 > index_p2) {
        unsigned int temp = index_p1;
        index_p1 = index_p2;
        index_p2 = temp;
    }
    
    if ((index_p2 == index_p1+1) or (index_p2 == polygon.size()-1 and index_p1 == 0)) {
        //std::cout<<"p1 y p2 son adyacentes. Retorna false\n";
        return false;
    }

    //Hasta aqui sabemos que p1-p2 no forman un lado del poligono (no son adyacentes)
    
    Point intersection; //punto donde se guarda la interseccion

    //Calculamos la interseccion entre cada lado del poligono y el lado p1-p2 y la guardamos en intersection
    //Recorremos cada segmento (polygon[i]-polygon[i+1]
    for (unsigned int i = 0; i < polygon.size()-1; i++) {
        //Si la linea p1-p2 se intersecta con p_i-p_(i+1) => no es una diagonal valida
        if (getLineIntersection(polygon[index_p1]->p, polygon[index_p2]->p, polygon[i]->p, polygon[i+1]->p, intersection, false)) {
            std::cout<<"Punto de interseccion = "; intersection.print(true);
            return false;
        }
    }
    //Comprobacion del ultimo con el primero
    if (getLineIntersection(polygon[index_p1]->p, polygon[index_p2]->p, polygon.back()->p, polygon.front()->p, intersection, false)) {
        std::cout<<"Punto de interseccion = "; intersection.print(true);
        return false;
    }
    
    //Hasta aquí, sabemos que la diagonal p1-p2 no se intersecta con ningun segmento del poligono ni es igual a un lado
    unsigned int index_to_use = index_p1 + 1;
    if (index_to_use >= polygon.size())//index_p1 es justo el ultimo del poligono
        index_to_use = 0;//usamos el primero entonces
    
    //Ahora debemos comprobar que es interna
    
    //Calculamos el angulo entre p1-p2 y p1-v_i. Notar que p1 es el pivote y por eso va en el medio
    float angle = angleBetweenSegments(polygon[index_to_use]->p, polygon[index_p1]->p, polygon[index_p2]->p); 
    
    //std::cout<<"Angle = "<<angle<<'\n';
    //Si el angulo entre p1-p2 y el segmento p_i-pi+1 con p_i = p1 es positivo => diagonal externa
    if (angle > 0) {
        //std::cout<<"Angulo positivo\n";
        return true;
    }
    else
        return false;
}



};

#endif
