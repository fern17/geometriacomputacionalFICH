/*
 * =====================================================================================
 *
 *       Filename:  lineas.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2013 05:01:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Point.h"
#include <cmath>
#include <iostream>

class TriangleStatic {
    public:
    Point p1;
    Point p2;
    Point p3;
    TriangleStatic(Point _p1, Point _p2, Point _p3) : p1(_p1), p2(_p2), p3(_p3) {}
    void print(bool enter) {
        std::cout<<" p1 = "; this->p1.print(false);
        std::cout<<" p2 = "; this->p2.print(false);
        std::cout<<" p3 = "; this->p3.print(false);
        if (enter) 
            std::cout<<"\n";
    }   
};

bool static getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &intersection, bool lessequal = true) {
    Point s1;
    Point s2;
    s1.x = p1.x - p0.x;     s1.y = p1.y - p0.y;
    s2.x = p3.x - p2.x;     s2.y = p3.y - p2.y;

    float s, t;
    float denominator = (-s2.x * s1.y + s1.x * s2.y);
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
float static crossProduct(const Point &v1, const Point &v2) {
    return v1.x*v2.y - v1.y*v2.x;
}
bool static sameSide(Point p1, Point p2, Point q1, Point q2) {
    Point q21 = q2 - q1;
    Point p1q1 = p1 - q1;
    Point p2q1 = p2 - q1;
    float cp1 = crossProduct(q21, p1q1);
    float cp2 = crossProduct(q21, p2q1);
    float dot = cp1*cp2;
    if (dot > 0) return true;
    else return false;
}

bool static pointInTriangle(Point P, Point Ta, Point Tb, Point Tc) {
    if (sameSide(P, Ta, Tb, Tc) and sameSide(P, Tb, Ta, Tc) and sameSide(P, Tc, Ta, Tb)) 
        return true;
    else
        return false;
}

bool static triangleOverlap(TriangleStatic T1, TriangleStatic T2) {
    //Se debe probar los 3 lados de T1 contra los 3 lados de T2
    //Si no se intersectan, probar 3 puntos de de T1 dentro de T2 y viceversa
    //
    //
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
int main() {
    Point pa(200, 360);
    Point pb(10,400);
    Point pc(160, 240);
    Point qa(10,400);
    Point qb(140,340);
    Point qc(200,360);
    TriangleStatic T1(pa,pb,pc);
    TriangleStatic T2(qa,qb,qc);
    
    bool inside = triangleOverlap(T1,T2);
    if (inside)
        std::cout<<"intersectan\n";
    else
        std::cout<<"nope\n";
    return 0;
}
