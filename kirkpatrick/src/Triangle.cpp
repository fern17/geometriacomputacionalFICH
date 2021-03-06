#include "Triangle.h"
#include "Vertex.h"
#include <iostream>
#include <GL/glut.h>

//Imprime a la salida estandar
void Triangle::print(bool enter) {
    std::cout<<"p1 = "; this->p1->p.print(false);
    std::cout<<" p2 = "; this->p2->p.print(false);
    std::cout<<" p3 = "; this->p3->p.print(false);
    if (enter) 
        std::cout<<"\n";
}

//True si v1 y v2 forman un segmento de este triangulo
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

    if (not res1) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p1\n";
    }
    if (not res2) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p2\n";
    }
    if (not res3) {
        std::cout<<"Advertencia: no se pudo borrar el triangulo de p3\n";
    }
}

//OpenGL
void Triangle::draw() {
    glBegin(GL_TRIANGLES);
        glVertex2f(this->p1->p.x, this->p1->p.y);
        glVertex2f(this->p2->p.x, this->p2->p.y);
        glVertex2f(this->p3->p.x, this->p3->p.y);
    glEnd();
}
