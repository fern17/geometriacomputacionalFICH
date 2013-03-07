#ifndef _UTILS_CPP_
#define _UTILS_CPP_
#include "Vertex.h"
#include "Point.h"
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TriangleStatic.h"

namespace utils{

const static float RADIAN = 180/M_PI;

std::string static ctos(char *c) {
    std::stringstream ss;
    ss<<c;
    return ss.str();
}

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in intersection
// Si las lineas son coincidentes, retorna falso
bool static getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &intersection, bool lessequal = true) {
    Point s1;
    Point s2;
    s1.x = p1.x - p0.x;     s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;     s2.y = p3.y - p2.y;

    float s, t;
    float denominator = (-s2.x * s1.y + s1.x * s2.y);   //producto vectorial
    if (fabs(denominator) < 0.000001) //denominador igual a cero
        return false;
    s = (-s1.y * (p0.x - p2.x) + s1.x * (p0.y - p2.y)) / denominator;
    t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / denominator;

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

/*
float static dotProduct(const Point &v1, const Point &v2) {
    return v1.x*v2.x + v1.y*v2.y;
}*/

float static crossProduct(const Point &v1, const Point &v2) {
    return v1.x*v2.y - v1.y*v2.x;
}
/*
float static module(const Point &v) {
    return sqrt(pow(v.x, 2) + pow(v.y,2));
}

float static moduleSquared(const Point &v) {
    return (pow(v.x, 2) + pow(v.y,2));
}*/
 
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

/*
float static angleBetweenVectors(const Point &v1, const Point &v2) {
    return (atan2(v2.y,v2.x) - atan2(v1.y,v1.x))*RADIAN;
}
*/

/*
//calcula el angulo angle(p1,p2,p3), donde p2 es el punto en comun
float static angleBetweenSegments(Point p1, Point p2, Point p3) {
    //Primero calculamos los vectores v1 y v2
    Point v1;
    Point v2;
    v1 = p1 - p2;
    v2 = p3 - p2;
    v1.print(false);
    v2.print(false);
    //Ahora calculamos el angulo teniendo los dos vectores
    return angleBetweenVectors(v1, v2);
}*/

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

//Prueba si V3 esta entre V1 y V2 CCW
//http://stackoverflow.com/questions/693806/how-to-determine-whether-v3-is-between-v1-and-v2-when-we-go-from-v1-to-v2-counte/693969#693969
bool static vectorBetweenCCW(Point V3, Point V1, Point V2) {
    float c12 = crossProduct(V1,V2);
    float c13 = crossProduct(V1,V3);
    float c32 = crossProduct(V3,V2);
    //Signos de los productos
    bool c12p = c12 >= 0;
    bool c13p = c13 >= 0;
    bool c32p = c32 >= 0;
    if (  (c12p and c13p and c32p) or //si los 3 son positivos
          ((not c12p) and (c13p and c32p))){ //c12 negativo pero c13 and c32 positivo
        return true;
    } else { 
        return false;
    }
}

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
    
    /*
    unsigned int index_to_use = index_p1 + 1;
    if (index_to_use >= polygon.size())//index_p1 es justo el ultimo del poligono
        index_to_use = 0;//usamos el primero entonces
    
    //Ahora debemos comprobar que es interna
   
    polygon[index_to_use]->p.print(true); 
    polygon[index_p1]->p.print(true); 
    polygon[index_p2]->p.print(true); 
    //Calculamos el angulo entre p1-p2 y p1-v_i. Notar que p1 es el pivote y por eso va en el medio
    float angle = angleBetweenSegments(polygon[index_to_use]->p, polygon[index_p1]->p, polygon[index_p2]->p); 
    std::cout<<"Angle = "<<angle<<'\n';
    //Si el angulo entre p1-p2 y el segmento p_i-pi+1 con p_i = p1 es positivo => diagonal externa
    if (angle > 0) {
        //std::cout<<index_p1<<' '<<index_p2<<'\n';
        std::cout<<"Angulo positivo\n";
        return true;
    }
    else
        return false;
    */

    unsigned int index_next;
    if (index_p1 == polygon.size()-1)//index_p1 es justo el ultimo del poligono
        index_next = 0;//usamos el primero entonces
    else
        index_next = index_p1 + 1;

    unsigned int index_prev;
    if( index_p1 == 0)
        index_prev = polygon.size()-1;//index_p1 es justo el primero del poligono
    else
        index_prev = index_p1 - 1;

    Point v1 = polygon[index_next]->p - polygon[index_p1]->p;
    Point v2 = polygon[index_prev]->p - polygon[index_p1]->p;
    Point v3 = polygon[index_p2]->p - polygon[index_p1]->p;

    if (vectorBetweenCCW(v3, v1, v2)) {
        return true;
    } else {
        return false;
    }
}

/*
function SameSide(p1,p2, a,b)
    cp1 = CrossProduct(b-a, p1-a)
    cp2 = CrossProduct(b-a, p2-a)
    if DotProduct(cp1, cp2) >= 0 then return true
    else return false
function PointInTriangle(p, a,b,c)
    if SameSide(p,a, b,c) and SameSide(p,b, a,c)
        and SameSide(p,c, a,b) then return true
    else return false
*/

bool static sameSide(Point p1, Point p2, Point q1, Point q2) {
    Point q21 = q2 - q1;
    Point p1q1 = p1 - q1;
    Point p2q1 = p2 - q1;
    float cp1 = crossProduct(q21, p1q1);
    float cp2 = crossProduct(q21, p2q1);
    float dot = cp1*cp2;
    if (fabs(dot) < 0.00001 or dot > 0) return true;//>= para incluir fronteras
    //if (dot > 0) return true;       //> para excluir fronteras
    else return false;
}

//Un punto esta dentro de un triangulo si y solo si esta del mismo lado de los 3 segmentos
bool static pointInTriangle(Point P, Point Ta, Point Tb, Point Tc) {
    if (sameSide(P, Ta, Tb, Tc) and sameSide(P, Tb, Ta, Tc) and sameSide(P, Tc, Ta, Tb)) 
        return true;
    else
        return false;
}

//Se debe probar los 3 lados de T1 contra los 3 lados de T2
//Si no se intersectan, probar 3 puntos de de T1 dentro de T2 y viceversa
bool static triangleOverlap(TriangleStatic T1, TriangleStatic T2) {
    if (T1 == T2) return true;
    
    Point T1a = T1.p1;
    Point T1b = T1.p2;
    Point T1c = T1.p3;
    Point T2a = T2.p1;
    Point T2b = T2.p2;
    Point T2c = T2.p3;
   
    Point phantom;

    //Primero probamos los 3 lados de T1 contra los 3 lados de T2
    bool intersection;
    intersection = getLineIntersection(T1a, T1b, T2a, T2b, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1a, T1b, T2a, T2c, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1a, T1b, T2b, T2c, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1b, T1c, T2a, T2b, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1b, T1c, T2a, T2c, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1b, T1c, T2b, T2c, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1c, T1a, T2a, T2b, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1c, T1a, T2a, T2c, phantom, false);
    if(intersection) return true;
    else intersection = getLineIntersection(T1c, T1a, T2b, T2c, phantom, false);
    if(intersection) return true;
    
    bool inside;
    //Ahora probamos cada punto de T1 dentro de T2
    inside = pointInTriangle(T1a, T2a, T2b, T2c);
    if(inside) return true;
    else inside = pointInTriangle(T1b, T2a, T2b, T2c);
    if(inside) return true;
    else inside = pointInTriangle(T1c, T2a, T2b, T2c);
    //Ahora probamos cada punto de T2 dentro de T1
    if(inside) return true;
    else inside = pointInTriangle(T2a, T1a, T1b, T1c);
    if(inside) return true;
    else inside = pointInTriangle(T2b, T1a, T1b, T1c);
    if(inside) return true;
    else inside = pointInTriangle(T2c, T1a, T1b, T1c);
    if(inside) return true;
    else return false; //no esta dentro del triangulo
}

};
#endif
