#include "Triangle.h"
#include "Vertex.h"
#include <iostream>


void Triangle::print(bool enter) {
    std::cout<<"p1 = "; this->p1->p.print(false);
    std::cout<<" p2 = "; this->p2->p.print(false);
    std::cout<<" p3 = "; this->p3->p.print(false);
    if (enter) 
        std::cout<<"\n";
}

bool Triangle::isSegment(Vertex *v1, Vertex *v2) {
    if (v1 == this->p1) {
        if ((v2 == this->p2) or (v2 == this->p3) ) 
            return true;
    }
    if (v1 == this->p2) {
        if ((v2 == this->p1) or (v2 == this->p3) ) 
            return true;
    }
    if (v1 == this->p3) {
        if ((v2 == this->p1) or (v2 == this->p2) ) 
            return true;
    }
    return false;
}

//Borra la referencia de los puntos a este triangulo
void Triangle::deleteAllPoints() {
    bool res1 = p1->deleteTriangle(this);
    bool res2 = p2->deleteTriangle(this);
    bool res3 = p3->deleteTriangle(this);
    std::cout<<"Procesando el triangulo: ";
    this->print(true);

    if (res1) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p1\n";
    }
    if (res2) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p2\n";
    }
    if (res3) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p3\n";
    }
}
