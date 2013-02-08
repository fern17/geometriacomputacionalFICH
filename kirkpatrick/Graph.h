#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Point.h"
#include "Vertex.h"
#include "Triangle.h"
#include <vector>
#include <string>

class Graph {
    std::vector<Vertex> points;     //Conjunto de puntos del grafo
    std::vector<Triangle> triangles;//Conjunto de triangulos del grafo
    
    public:
    Graph(std::string f_vertex, std::string f_neighbor, std::string f_triangles);//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
    void printStructure(); //imprime la estructura completa
    bool deletePoint(Point &P);     //Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
    void retriangulate(Vertex *vertex_to_delete); //Dado un vertice para borrar, genera nuevas vecindades
    int searchPoint(const Point &P); //Dado un punto, busca el vertice que lo referencia. 
                //Retorna el indice en el vector de vertices o -1 si nadie lo referencia (no se encontro)

};

#endif
