#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Point.h"
#include "Vertex.h"
#include "Triangle.h"
#include <list>
#include <string>

class Graph {
    std::list<Vertex> points;     //Conjunto de puntos del grafo
    std::list<Triangle> triangles;//Conjunto de triangulos del grafo
    
    public:
    Graph(std::string f_vertex, std::string f_neighbor, std::string f_triangles);//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
    void printStructure(); //imprime la estructura completa
    unsigned int size();    
    //retriangulacion
    bool findValidDiagonal(std::vector<Vertex *> polygon, unsigned int &p1, unsigned int &p2); //encuentra una diagonal valida en polygon
    void retriangulate(std::vector<Vertex *> polygon); //retriangula recursivamente el poligno
    void retriangulate(Vertex *vertex_to_delete); //Dado un vertice para borrar, genera nuevas vecindades

    //borrado
    int searchPoint(const Point &P); //Dado un punto, busca el vertice que lo referencia. 
                //Retorna el indice en el vector de vertices o -1 si nadie lo referencia (no se encontro)
    bool deletePoint(Point &P);     //Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
    bool deleteVertex(Vertex *point_to_triangulate);    
    void deleteNearest(Point &P);

    //Kirkpatrick
    void kirkpatrickDeletion(unsigned int max_degree);
    void unmarkAllVertex();
    std::vector<Vertex *> selectVertexToDelete(unsigned int max_degree);
    
    //opengl
    void drawPoints();
    void drawLines();
};

#endif
