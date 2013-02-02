#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <vector>
#include "Point.h"

class Triangle;
class Vertex{ 
    public:
    Point p;                                    //Punto que representa este vertice
    std::vector<Vertex *> neighbors;            //Punteros a todos sus vecinos
    std::vector<Triangle *> triangles;          //Punteros a los triangulos vecinos

    Vertex(float _x, float _y);
    void addNeighbor(Vertex * _newneighbor);    //Agrega un vecino a la lista de vecinos
    bool isNeighbor(Vertex * neighbor);         //Dado un vertice, se fija si es vecino
    bool deleteNeighbor(Vertex * neighbor);     //Borra un vecino de la lista de vecinos. 
            //Ademas, debe llamar a ese vecino para que lo borre al vertice actual de su lista
    unsigned int deleteAllNeighbors();           //Recorre todos los vecinos y llama a deleteNeighbor. 
        //Retorna la cantidad de vecinos borrados.
    bool operator == (const Vertex &V);         //Igualdad con respecto al punto p
    int searchNeighbor(Vertex *V);        //Dado un vecino, devuelve la posicion donde esta en el vector de vecinos
}; 

#endif
