#ifndef _NODE_H_
#define _NODE_H_
#include <vector>

class TriangleStatic;
class Node {
    public:
    Node *father;               //puntero al padre
    std::vector<Node *> child;  //Vector con todos los hijos
    TriangleStatic *triangle;          //Triangulo que representa este nodo
    
    Node(TriangleStatic T);                            //Constructor sin padre
    Node(TriangleStatic T, Node *new_father);          //Constructor por defecto
    void addChild(Node *new_child);  //Agrega un hijo
    void setFather(Node *new_father); //Cambia el padre 
    void deleteChild(Node *child_to_delete); //borra un hija
    void print(unsigned int level);
};

#endif
