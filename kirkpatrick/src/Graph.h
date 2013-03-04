#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Point.h"
#include "Vertex.h"
#include "Triangle.h"
#include "TriangleStatic.h" 

#include <list>
#include <string>

//Declaraciones por adelantado
class Point;
class Vertex;
class Triangle;
class TriangleStatic;

//Clase grafo: tiene una lista de vertices y una lista de triangulos
class Graph {
public:
    std::list<Vertex> points;       //Conjunto de puntos del grafo
    std::list<Triangle> triangles;  //Conjunto de triangulos del grafo
    
    Graph(std::string f_vertex, std::string f_neighbor, std::string f_triangles);//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
    void printStructure();          //imprime la estructura completa
    unsigned int size();            //Retorna la cantidad de puntos
    //Retriangulacion
    bool findValidDiagonal(std::vector<Vertex *> polygon, unsigned int &p1, unsigned int &p2); //encuentra una diagonal valida en polygon
    void retriangulate(std::vector<Vertex *> polygon); //retriangula recursivamente el poligono. Llama al otro retriangulate
    void retriangulate(Vertex *vertex_to_delete); //Dado un vertice para borrar, genera nuevas vecindades

    //borrado
    int searchPoint(const Point &P); //Dado un punto, busca el vertice que lo referencia. 
                //Retorna el indice en el vector de vertices o -1 si nadie lo referencia (no se encontro)
    bool deletePoint(Point &P);     //Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
    bool deleteVertex(Vertex *point_to_triangulate); //Dado un vertice, lo borra y llama a la retriangulacion
    void deleteNearest(Point &P);   //Dado un punto P, borra el vertice mas cercano

    //kirkpatrick
    unsigned int kirkpatrickDeletion(unsigned int max_degree);      //Borra un vertice de grado predefinido
    void unmarkAllVertex();        //Desmarca todos los vertices (vertex->marked = false)
    std::vector<Vertex *> selectVertexToDelete(unsigned int max_degree);
    TriangleStatic getBoundingTriangle();   //Retorna el triangulo estatico formado por los primeros 3 puntos, que debe ser el bounding triangle
    
    //opengl
    void drawPoints();
    void drawTriangles();
    void drawLines();
};

#endif
