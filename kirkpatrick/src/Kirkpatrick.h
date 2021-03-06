#ifndef _KIRKPATRICK_H_
#define _KIRKPATRICK_H_

#include "Node.h"
#include "Graph.h"
#include <vector>

//Clase que almacena la estructura de Kirkpatrick
class Kirkpatrick {
    public:
    Node *root;                         //puntero a la raiz
    Graph *G;
    unsigned int max_degree;            //maximo grado que se va a aceptar los puntos
    std::vector<Node *> nodes_prev;     //en este vector se almacenaran los nodos que se agregan en cada nivel del arbol, para iterar en el nivel siguiente

    Kirkpatrick(Graph * _G, unsigned int _max_degree);          //constructor vacio
    void build(int max_steps = -1);                             //Inicializa el DAG y realiza las iteraciones llamando a step
    bool step();                                                //Realiza una iteracion del DAG
    void print();                                               //Imprime el arbol
    bool searchPoint(Point P, std::vector<TriangleStatic> &ret_val);         //Le pregunta la nodo raiz si el punto esta dentro suyo y lanza la recursion
};

#endif
