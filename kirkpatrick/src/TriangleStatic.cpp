#include "Triangle.h"
#include "TriangleStatic.h"
#include "Vertex.h"
#include <GL/glut.h>
#include <iostream>

//constructor vacio que le asigna un tag 
TriangleStatic::TriangleStatic() {      
    this->triangletag = TriangleStatic::nextTag();
} 

//constructor con puntos. Le asigna un tag
TriangleStatic::TriangleStatic(Point _p1, Point _p2, Point _p3) { 
    this->p1 = _p1;
    this->p2 = _p2;
    this->p3 = _p3;
    this->triangletag = TriangleStatic::nextTag();
}

//Dado un triangulo, devuelve un TriangleStatic con sus mismos puntos
TriangleStatic TriangleStatic::buildFromTriangle(Triangle T) {
    Point p1 = T.p1->p;
    Point p2 = T.p2->p;
    Point p3 = T.p3->p;
    TriangleStatic ret_val (p1, p2, p3);
    return ret_val;
}

//True si tienen exactamente los mismos puntos
bool TriangleStatic::operator ==(const TriangleStatic &compare_to) {
    return  (this->p1 == compare_to.p1) and
            (this->p2 == compare_to.p2) and
            (this->p3 == compare_to.p3);
}

//Imprime el triangulo a la salida estandar
void TriangleStatic::print(bool enter) {
    std::cout<<this->triangletag<<'\t';
    std::cout<<" p1 = "; this->p1.print(false);
    std::cout<<" p2 = "; this->p2.print(false);
    std::cout<<" p3 = "; this->p3.print(false);
    if (enter) 
        std::cout<<"\n";
}

//OpenGL
void TriangleStatic::draw() {
    glBegin(GL_TRIANGLES);
        glVertex2f(this->p1.x, this->p1.y);
        glVertex2f(this->p2.x, this->p2.y);
        glVertex2f(this->p3.x, this->p3.y);
    glEnd();
}
