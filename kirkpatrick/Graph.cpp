#include "Graph.h"

//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
Graph::Graph(std::string filename) {

}    

//Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
bool Graph::deletePoint(Point &P) {      
    int position = this->searchPoint(P);
    
    if (position == -1) 
        return false; //Point no encontrado
    else {
        this->retriangulate(points[position]);
        unsigned int count_of_deleted_neighbors = this->points[position]->deleteAllNeighbors();
        this->points.erase(this->points.begin()+position);
        return true;
    }
}

//Dado un vertice para borrar, genera nuevas vecindades
void Graph::retriangulate(Vertex *vertex_to_delete) {
    //Elegir un vecino cualquiera y tirar aristas a todos los otros
    //Primero elegimos un vecino cualquiera:
    Vertex *pivot = vertex_to_delete->neighbors.front();
    //Obtenemos todos los vecinos del vertice a borrar
    std::vector<Vertex *> neighbors_of_todelete = vertex_to_delete->neighbors;
    for (unsigned int i = 0; i < neighbors_of_todelete.size(); i++) {
        if (neighbors_of_todelete[i] == pivot or  //Si es el pivot, no hago nada
                neighbors_of_todelete[i] == vertex_to_delete)  //comparacion extra que no deberia pasar nunca
            continue;
        else {
            //Agrego una vecindad de pivot a un vecino (antiguo vecino de vertex_to_delete
            neighbors_of_todelete[i]->addNeighbor(pivot); 
        }
    }
}

//Dado un punto, busca el vertice que lo referencia. 
//Retorna el indice en el vector de vertices o -1 si nadie lo referencia (no se encontro)
int Graph::searchPoint(const Point &P) {
    for (unsigned int i = 0; i < this->points.size(); i++) {
        if (this->points[i]->p == P) {
            return i;
        }
    }
    return -1;
}
