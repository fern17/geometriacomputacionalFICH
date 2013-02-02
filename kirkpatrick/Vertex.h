#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include "Triangle.h"
#include "Point.h"

class Vertex{ 
    Point p;                                    //Punto que representa este vertice
    std::vector<Vertex *> neighbors;            //Punteros a todos sus vecinos
    std::vector<Triangle *> triangles;          //Punteros a los triangulos vecinos
    public:
    Vertex(float _x, float _y);
    void addNeighbor(Vertex * _newneighbor);    //Agrega un vecino a la lista de vecinos
    bool isNeighbor(Vertex * neighbor);         //Dado un vertice, se fija si es vecino
    bool deleteNeighbor(Vertex * neighbor);     //Borra un vecino de la lista de vecinos. 
            //Ademas, debe llamar a ese vecino para que lo borre al vertice actual de su lista
};

#endif
