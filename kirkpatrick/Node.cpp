#include "Node.h"
#include "TriangleStatic.h"
#include <iostream>
#include <cstdio>

Node::Node(TriangleStatic T) {          //Constructor sin padre
    this->triangle = new TriangleStatic(T);
}

Node::Node(TriangleStatic T, Node *new_father) {          //Constructor por defecto
    this->triangle = new TriangleStatic(T);
    this->father = new_father;
}

void Node::addChild(Node *new_child) {  //Agrega un hijo
    this->child.push_back(new_child);
}

void Node::setFather(Node *new_father) { //le cambia el padre
    this->father = new_father;
}

void Node::deleteChild(Node *child_to_delete) {
    for (unsigned int i = 0; i < this->child.size(); i++) {
        if (this->child[i] == child_to_delete) {
            this->child.erase(this->child.begin()+i);
            return;
        }
    }
}

void Node::print(unsigned int level) {
    //imprimimos tabulaciones para identar
    for (unsigned int i = 0; i < level; i++)
        std::cout<<"  ";
    //Muestra el triangulo
    this->triangle->print(true);
    
    std::cout<<"current level = "<<level<< "\n"; getchar();
    //imprime los hijos
    for (unsigned int i = 0; i < this->child.size(); i++) {
        this->child[i]->print(level+1);
    }
}
