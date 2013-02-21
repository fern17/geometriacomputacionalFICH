#include "Node.h"

Node::Node(Triangle &T, Node *new_father) {          //Constructor por defecto
    this->triangle = T;
    this->father = new_father;
}

void Node::addChild(Node *new_child) {  //Agrega un hijo
    this->child.push_back(new_child);
}

