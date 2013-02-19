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
    unsigned int degree;
    Vertex(float _x, float _y);
    void print();                               //imprime el punto, sus vecinos y triangulos
    bool addTriangle(Triangle * _newtriangle);  //agrega un triangulo en la lista, solo si no lo tenia ya
    bool isTriangle(Triangle * _newtriangle);   //true si ya tiene a este triangulo en la lista de triangulos a los que pertenece
    void addNeighbor(Vertex * _newneighbor);    //Agrega un vecino a la lista de vecinos
    void addNeighborCCW(Vertex *new_neighbor); //Agrega un vecino a la lista de vecinos pero lo ubica de manera que el array quede ordenado
    void setNeighbors(std::vector<Vertex *> _newneighbors); //Agrega TODOS los vecinos a la lista de vecinos
    bool isNeighbor(Vertex * neighbor);         //Dado un vertice, se fija si es vecino
    bool deleteNeighbor(Vertex * neighbor);     //Borra un vecino de la lista de vecinos. 
            //Ademas, debe llamar a ese vecino para que lo borre al vertice actual de su lista
    unsigned int deleteAllNeighbors();           //Recorre todos los vecinos y llama a deleteNeighbor. 
        //Retorna la cantidad de vecinos borrados.
    bool operator == (const Vertex &V);         //Igualdad con respecto al punto p
    int searchNeighbor(Vertex *V);              //Dado un vecino, devuelve la posicion donde esta en el vector de vecinos
    bool deleteTriangle(Triangle *tri);         //Dado un triangulo, lo borra de la lista de triangulos. Retorna true si lo pudo borrar
    void deleteTriangles(Vertex *related_to); //Le digo a mis vecinos que borre todos los triangulos que nos tienen como lado
    std::vector<Triangle *> findTriangles(Vertex *related_to); //Dado un vertice, devuelve los indices en el array de triangulos donde se halla 
                                                                //un triangulo que tiene a this y related_to como lado

}; 

#endif
