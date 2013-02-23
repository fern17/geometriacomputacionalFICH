#include "Node.h"
#include "TriangleStatic.h"
#include "Point.h"
#include "utils.cpp"
#include <iostream>
#include <algorithm>
#include <queue>
Node::Node(TriangleStatic T) {          //Constructor sin padre
    this->triangle = new TriangleStatic(T);
}

void Node::addChild(Node *new_child) {  //Agrega un hijo
    if (not isChild(new_child))
        this->child.push_back(new_child);
}

bool Node::isChild(Node *c) { //true si C es hijo de this
    for (unsigned int i = 0; i < this->child.size(); i++) 
        if (this->child[i] == c) 
            return true;
    return false;
}

void Node::deleteChild(Node *child_to_delete) {
    std::vector<Node *>::iterator p = this->child.begin();
    while (p != this->child.end()) {
        if (*p == child_to_delete) {
            p = this->child.erase(p);
        }
        else 
            p++;
    }
}

bool Node::operator ==(const Node &compare_to) {
    return this->triangle == compare_to.triangle;
}

void Node::print(unsigned int level) {
    //imprimimos tabulaciones para identar
    
    
    for (unsigned int i = 0; i < level; i++)  std::cout<<"  ";
    //Muestra el triangulo
    std::cout<<"l="<<level<<" "; this->triangle->print(true);
    
    //std::getchar();
    //imprime los hijos
    for (unsigned int i = 0; i < this->child.size(); i++) {
        this->child[i]->print(level+1);
    }

    /*
    //std::cout<<"current level = "<<level<< "\n"; 
    std::queue<Node *> to_print;
    //muestra todos sus hijos
    for (unsigned int i = 0; i < this->child.size(); i++) {
        Node *current = this->child[i];
        for (unsigned int i = 0; i < level; i++)
            std::cout<<"  ";
        current->triangle->print(true); 
        to_print.push(current); //lo agrega a la cola
    }
    while (not to_print.empty()) {
        Node *current = to_print.front();
        to_print.pop();
        current->print(level+1);
    }
    */

}

bool Node::search(Point P, TriangleStatic &ret_val, unsigned int pasos) {
    if (utils::pointInTriangle(P, this->triangle->p1, this->triangle->p2, this->triangle->p3)){
        //std::cout<<"Dentro de "; this->triangle->print(true);
        if (this->child.empty()) {
            ret_val = *this->triangle;
            std::cout<<"Se hicieron "<<pasos<<" pasos para encontrar el punto\n";
            return true;
        }
        else {
            for (unsigned int i = 0; i < this->child.size(); i++) {
                if (this->child[i]->search(P, ret_val, pasos+1))
                    return true;
            }
        }
    }
    return false;
}
