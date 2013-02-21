#ifndef _KIRKPATRICK_H_
#define _KIRKPATRICK_H_

#include "Node.h"
#include "Graph.h"

class Kirkpatrick {
    public:
    Node *root;             //puntero a la raiz

    Kirkpatrick();          //constructor vacio
    build(Graph *G);        //Construye el DAG

};

#endif
