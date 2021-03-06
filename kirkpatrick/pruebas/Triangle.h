#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

class Vertex;
class Triangle {
    public:
    Vertex *p1;
    Vertex *p2;
    Vertex *p3;
    Triangle(Vertex *_p1, Vertex * _p2, Vertex *_p3) : p1(_p1), p2(_p2), p3(_p3) {}
    void print(bool enter = false);
    bool isSegment(Vertex *v1, Vertex *v2);
    void deleteAllPoints();
};

#endif
