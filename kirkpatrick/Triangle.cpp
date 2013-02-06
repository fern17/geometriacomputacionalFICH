#include "Triangle.h"
#include "Vertex.h"
#include <iostream>


void Triangle::print(bool enter) {
    std::cout<<"p1 = "; this->p1->p.print(false);
    std::cout<<"p2 = "; this->p2->p.print(false);
    std::cout<<"p3 = "; this->p3->p.print(false);
    if (enter) 
        std::cout<<"\n";
}
