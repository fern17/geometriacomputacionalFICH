#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Vertex.h"

class Triangle {
    Vertex *p1;
    Vertex *p2;
    Vertex *p3;
    public:
    Triangle(Vertex * _p1, Vertex * _p2, Vertex * _p3) : p1(_p1), p2(_p2), p3(_p3) {}
};

#endif
