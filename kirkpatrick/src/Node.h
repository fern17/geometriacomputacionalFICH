#ifndef _NODE_H_
#define _NODE_H_
#include <vector>
//Declaracion por adelantado
class Point;
class TriangleStatic;
//Clase que almacena un nodo de la estructura de Kirkpatrick
class Node {
    public:
    std::vector<Node *> child;          //Vector con todos los hijos
    TriangleStatic *triangle;           //Triangulo que representa este nodo
    
    Node(TriangleStatic T);             //Constructor  
    bool operator ==(const Node &compare_to);   //True si representan el mismo triangulo
    bool isChild(Node *c);              //true si C es hijo de this
    void addChild(Node *new_child);     //Agrega un hijo
    void deleteChild(Node *child_to_delete);    //borra un hijo
    void print(unsigned int level);     //Muestra el triangulo tabulado a tantos niveles
    bool search(Point P, std::vector<TriangleStatic> &ret_val, unsigned int pasos);  //Le pregunta si P esta dentro de si mismo. Y llama a sus hijos
};

#endif
