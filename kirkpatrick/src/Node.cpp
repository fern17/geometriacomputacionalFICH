#include "Node.h"
#include "TriangleStatic.h"
#include "Point.h"
#include "utils.cpp"
#include <iostream>
#include <algorithm>

//Constructor
Node::Node(TriangleStatic T) {          
    this->triangle = new TriangleStatic(T);
}

//Agrega un hijo si ya no lo tenia
void Node::addChild(Node *new_child) {  
    if (not isChild(new_child))
        this->child.push_back(new_child);
}

//true si C es hijo de this (esta en la lista de hijos)
bool Node::isChild(Node *c) { 
    for (unsigned int i = 0; i < this->child.size(); i++) 
        if (this->child[i] == c) 
            return true;
    return false;
}

//Borra el hijo, si es que esta en su lista de hijos. Recorre siempre todos los hijos, para evitar que quede repetido
void Node::deleteChild(Node *child_to_delete) {
    std::vector<Node *>::iterator p = this->child.begin();
    while (p != this->child.end()) { //busqueda
        if (*p == child_to_delete) {
            p = this->child.erase(p);
        }
        else 
            p++;
    }
}

//Compara los triangulos del nodo
bool Node::operator ==(const Node &compare_to) {
    return this->triangle == compare_to.triangle;
}

//Muestra el triangulo a la salida estandar
void Node::print(unsigned int level) {
    //imprimimos tabulaciones para identar
    for (unsigned int i = 0; i < level; i++)  
        std::cout<<"  ";
    
    //Muestra el triangulo
    std::cout<<"l="<<level<<" "; this->triangle->print(true);
    
    //imprime los hijos
    for (unsigned int i = 0; i < this->child.size(); i++) {
        this->child[i]->print(level+1);
    }
}

//Pregunta si P esta dentro mio. Si lo esta, llama a los hijos.
//Si soy nodo hoja, retorno mi triangulo por parametro
//El tercer parametro es para contar las comparaciones
bool Node::search(Point P, TriangleStatic &ret_val, unsigned int pasos) {
    if (utils::pointInTriangle(P, this->triangle->p1, this->triangle->p2, this->triangle->p3)){
        //Este nodo es hoja
        if (this->child.empty()) {
            ret_val = *this->triangle; //el valor de retorno es mi triangulo
            std::cout<<"Se hicieron "<<pasos<<" pasos para encontrar el punto\n"; //imprime la cantidad de comparaciones
            return true;                //retorna true para saber que se encontro
        }
        else {//Le pregunta por inclusion a todos sus hijos
            for (unsigned int i = 0; i < this->child.size(); i++) {
                if (this->child[i]->search(P, ret_val, pasos+1+i))
                    return true;
            }
        }
    }
    return false; //no esta dentro de este triangulo
}
