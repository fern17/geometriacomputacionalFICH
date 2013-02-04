#ifndef _UTILS_CPP_
#define _UTILS_CPP_

#include "Point.h"
#include <cmath>
namespace utils{

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in intersection
bool static getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &intersection)
//        float p1_x, float p1_y, 
//    float p2_x, float p2_y, float p3_x, float p3_y, float &i_x, float &i_y)
{
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




};

#endif
