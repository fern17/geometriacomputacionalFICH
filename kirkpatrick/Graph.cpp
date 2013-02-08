#include "Graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h>

//Lee desde un archivo las coordenadas de los vertices, las vecindades y los triangulos
Graph::Graph(std::string f_vertex, std::string f_neighbor, std::string f_triangles) {

    /*Lectura de las coordenadas de vertices   */
    std::ifstream file_v; 
    file_v.open(f_vertex.c_str());
    if(!file_v.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<f_vertex<<"\n";
        return;
    }
    
    //Lee la cantidad de puntos y reserva el espacio de vecinos en cada Vertex (para evitar problemas de punteros)
    unsigned int cantidad_puntos;
    file_v>>cantidad_puntos;
    this->points.reserve(cantidad_puntos);
    std::cout<<"Se soportaran "<<cantidad_puntos<<" puntos distintos.\n";
    
    float _x;
    float _y;
    std::cout<<"Leyendo puntos:\n";
    while (file_v>>_x and file_v>>_y) {
        Vertex v (_x, _y);
        v.p.print(true);
        v.neighbors.reserve(cantidad_puntos); //reserva espacio para los vecinos que pronto vendran
        this->points.push_back(v);
    }
    unsigned int points_read = this->points.size();
    std::cout<<points_read<<" puntos leidos\n";
    file_v.close();
    /*--------------------------------------------------------------------------*/

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
    /* ----------------------------------------------------------------------------- */

    /*Lectura de los triangulos   */
    
    std::ifstream file_t; 
    file_t.open(f_triangles.c_str());
    if(!file_t.is_open()) { //muestra error si no se pudo abrir el archivo
        std::cout<<"No se pudo abrir el archivo "<<f_triangles<<"\n";
        return;
    }
    
    //Lee la cantidad de triangulos y reserva el espacio en cada Vertex (para evitar problemas de punteros)
    unsigned int cantidad_triangulos;
    file_t>>cantidad_triangulos;
    this->triangles.reserve(cantidad_triangulos);
    std::cout<<"Se soportaran "<<cantidad_triangulos<<" triangulos distintos.\n";
    for (unsigned int i = 0; i < this->points.size(); i++) {
        this->points[i].triangles.reserve(cantidad_triangulos);
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
        std::cout<<_p1<<' '<<_p2<<' '<<_p3<< '\n';
        //Captura la direccion de memoria de los 3 vertices que componen este triangulo
        Vertex *v1 = &this->points[_p1]; 
        Vertex *v2 = &this->points[_p2]; 
        Vertex *v3 = &this->points[_p3]; 
        //Crea el triangulo
        Triangle tri (v1,v2,v3);
        
        this->triangles.push_back(tri);
        Triangle *tri_pointer = &this->triangles.back();
        //Agrega el triangulo a cada uno de los vertices que lo componen
        if(not v1->addTriangle(tri_pointer)) {
            std::cout<<"Error, no se pudo agregar el triangulo a "; v1->p.print();
        }
        
        if(not v2->addTriangle(tri_pointer)) {
            std::cout<<"Error, no se pudo agregar el triangulo a "; v2->p.print();
        }
        
        if(not v3->addTriangle(tri_pointer)) {
            std::cout<<"Error, no se pudo agregar el triangulo a "; v3->p.print();
        }
       
        std::cout<<"#"<<triangle_num<<" "; tri_pointer->print(true);
        
        triangle_num++;
    }
    std::cout<<triangle_num<<" triangulos leidos\n";
    file_t.close();
}    

void Graph::printStructure() {
    std::cout<<"Estructura del grafo:\n";
    std::cout<<"Puntos:\n";
    //Impresion de puntos
    for (unsigned int i = 0; i < this->points.size(); i++) {
        std::cout<<"#"<<i<<" "; this->points[i].print(); std::cout<<"\n";
    }
    std::cout<<"---------------------------------------------\n";

    std::cout<<"Triangulos:\n";
    //Impresion de triangulos
    for (unsigned int i = 0; i < this->triangles.size(); i++) {
        std::cout<<"#"<<i<<" "; this->triangles[i].print(true);
    }
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

void Graph::drawPoints() {
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < this->points.size(); i++) {
        Vertex *v = &this->points[i];
        glVertex2f(v->p.x, v->p.y);
    }
    glEnd();
}

void Graph::drawLines() {
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < this->points.size(); i++) {
        Vertex *v = &this->points[i];
        
        unsigned int cantidad_vecinos = v->neighbors.size();
        for (unsigned int j = 0; j < cantidad_vecinos; j++) {
            Vertex *u = v->neighbors[j];
            glVertex2f(v->p.x, v->p.y);
            glVertex2f(u->p.x, u->p.y);
        }
    }
    glEnd();
}
