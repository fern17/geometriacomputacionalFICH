#ifndef _NODE_H_
#define _NODE_H_
#include "Triangle.h"
#include <vector>

class Node {
    public:
    Node *father;               //puntero al padre
    std::vector<Node *> child;  //Vector con todos los hijos
    Triangle triangle;          //Triangulo que representa este nodo
    Node(Triangle &T, Node *new_father);          //Constructor por defecto
    addChild(Node *new_child);  //Agrega un hijo
    
};

#endif
