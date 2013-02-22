#ifndef _KIRKPATRICK_H_
#define _KIRKPATRICK_H_

#include "Node.h"
#include "Graph.h"

class Kirkpatrick {
    public:
    Node *root;             //puntero a la raiz

    Kirkpatrick();          //constructor vacio
    void build(Graph *G, unsigned int max_degree); //Construye el DAG
    void print();
};

#endif
