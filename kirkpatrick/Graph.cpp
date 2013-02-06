#include "Graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
Graph::Graph(std::string f_vertex, std::string f_neighbor, std::string f_triangles) {

    /*Lectura de las coordenadas de vertices   */
    std::ifstream file_v; 
    file_v.open(f_vertex.c_str());
    if(!file_v.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<f_vertex<<"\n";
        return;
    }
    
    float _x;
    float _y;
    std::cout<<"Leyendo puntos:\n";
    while (file_v>>_x and file_v>>_y) {
        Vertex v (_x, _y);
        v.p.print(true);
        this->points.push_back(v);
    }
    unsigned int points_read = this->points.size();
    std::cout<<points_read<<" puntos leidos\n";
    file_v.close();
    /*-----------------------*/

    /*Lectura de las vecindades de cada punto */
    std::ifstream file_n; 
    file_n.open(f_neighbor.c_str());
    if(!file_n.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<f_neighbor<<"\n";
        return;
    }
    
    int value;
    std::string s, line;
    std::stringstream ss, iss;
    unsigned int vertex_processing = 0;
    
    std::cout<<"Leyendo vecindades:\n";
    while(getline(file_n,line)){      //lee una linea entera
        iss<<line;

        std::vector<Vertex *> current_neighbors; //vecinos del vertex actual
        while(getline(iss,s,' ')){ //separa la linea entre los espacios
            //transforma de string a int
            ss<<s;
            ss>>value;
            if (value < 0 or value > this->points.size()) { //value invalido
                std::cout<<"Invalid neighbor: "<<value<<" in line "<<vertex_processing<<"\n";
                return;
            }
            Vertex *new_neighbor = &this->points[value]; //captura su direccion
            current_neighbors.push_back(new_neighbor); //agrega el vecino
            ss.str(""); //limpia la string asociada
            ss.clear(); //limpia el stream
        }
        //Una vez que leimos todos los vecinos, asignamos
        this->points[vertex_processing].setNeighbors(current_neighbors);
        iss.str(""); //limpia la string asociada
        iss.clear(); //limpia el stream
        vertex_processing++; //aumenta el contador de linea para el error
    }
    std::cout<<vertex_processing<<" vecindades leidas\n";
    file_n.close();
    /* ----------------- */

    /*Lectura de las coordenadas de vertices   */
    std::ifstream file_t; 
    file_t.open(f_triangles.c_str());
    if(!file_t.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<f_triangles<<"\n";
        return;
    }
    
    unsigned int _p1;
    unsigned int _p2;
    unsigned int _p3;
    unsigned int triangle_num = 0; //contador de puntos leidos
    std::cout<<"Leyendo puntos de triangulos:\n";
    while (file_t>>_p1 and file_t>> _p2 and file_t>>_p3) {
        //Comprobacion de indices invalidos
        if (_p1 < 0 or _p1 > points_read) {
            std::cout<<"Error: Indice del triangulo "<<triangle_num<<" invalido. Se leyo "<<_p1<<" pero solo hay "<<points_read<<" puntos.\n";
            continue;
        }
        if (_p2 < 0 or _p2 > points_read) {
            std::cout<<"Error: Indice del triangulo "<<triangle_num<<" invalido. Se leyo "<<_p2<<" pero solo hay "<<points_read<<" puntos.\n";
            continue;
        }
        if (_p3 < 0 or _p3 > points_read) {
            std::cout<<"Error: Indice del triangulo "<<triangle_num<<" invalido. Se leyo "<<_p3<<" pero solo hay "<<points_read<<" puntos.\n";
            continue;
        }
        
        Triangle tri (&this->points[_p1], &this->points[_p2], &this->points[_p3]);
        std::cout<<"# "<<triangle_num<<" "; tri.print(true);
       
        this->triangles.push_back(tri);
        triangle_num++;
    }
    std::cout<<triangle_num<<" triangulos leidos\n";
    file_t.close();
}    

//Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
bool Graph::deletePoint(Point &P) {      
    int position = this->searchPoint(P);
    
    if (position == -1) 
        return false; //Point no encontrado
    else {
        this->retriangulate(&points[position]);
        unsigned int count_of_deleted_neighbors = this->points[position].deleteAllNeighbors();
        this->points.erase(this->points.begin()+position);
        return true;
    }
}

//Dado un vertice para borrar, genera nuevas vecindades
//No funciona para caras no convexas
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
        if (this->points[i].p == P) {
            return i;
        }
    }
    return -1;
}
