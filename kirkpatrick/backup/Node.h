#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
class Point;
class TriangleStatic;
class Node {
    public:
    //Node *father;               //puntero al padre
    std::vector<Node *> child;  //Vector con todos los hijos
    TriangleStatic *triangle;          //Triangulo que representa este nodo
    
    Node(TriangleStatic T);                            //Constructor sin padre
    bool operator ==(const Node &compare_to);
    bool isChild(Node *c); //true si C es hijo de this
    void addChild(Node *new_child);  //Agrega un hijo
    //void setFather(Node *new_father); //Cambia el padre 
    void deleteChild(Node *child_to_delete); //borra un hija
    void print(unsigned int level);
    bool search(Point P, TriangleStatic &ret_val, unsigned int pasos);
};

#endif
