#include "Triangle.h"
#include "TriangleStatic.h"
#include "Vertex.h"
#include <iostream>
TriangleStatic TriangleStatic::buildFromTriangle(Triangle T) {
    Point p1 = T.p1->p;
    Point p2 = T.p2->p;
    Point p3 = T.p3->p;
    TriangleStatic ret_val (p1, p2, p3);
    return ret_val;
}

void TriangleStatic::print(bool enter) {
    std::cout<<"p1 = "; this->p1.print(false);
    std::cout<<" p2 = "; this->p2.print(false);
    std::cout<<" p3 = "; this->p3.print(false);
    if (enter) 
        std::cout<<"\n";
}

