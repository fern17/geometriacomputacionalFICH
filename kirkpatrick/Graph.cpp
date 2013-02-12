#include "Graph.h"
#include "utils.cpp"
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
    //this->points.reserve(cantidad_puntos);
    //std::cout<<"Se soportaran "<<cantidad_puntos<<" puntos distintos.\n";
    
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
    std::list<Vertex>::iterator it = this->points.begin();
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
            std::list<Vertex>::iterator it_nn = this->points.begin(); std::advance(it_nn, value);
            Vertex *new_neighbor = &*it; //captura su direccion
            //Vertex *new_neighbor = &this->points[value]; //captura su direccion
            current_neighbors.push_back(new_neighbor); //agrega el vecino
            ss.str(""); //limpia la string asociada
            ss.clear(); //limpia el stream
        }
        //Una vez que leimos todos los vecinos, asignamos
        it->setNeighbors(current_neighbors);
        it++;
        vertex_processing++;
        iss.str(""); //limpia la string asociada
        iss.clear(); //limpia el stream
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
    //this->triangles.reserve(cantidad_triangulos);
    //std::cout<<"Se soportaran "<<cantidad_triangulos<<" triangulos distintos.\n";
    std::list<Vertex>::iterator it_tri = this->points.begin();
    while (it_tri != this->points.end()) {
        it->triangles.reserve(cantidad_triangulos);
        it_tri++;
    }
    /*
    for (unsigned int i = 0; i < this->points.size(); i++) {
        this->points[i].triangles.reserve(cantidad_triangulos);
    }
    */

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
        //Captura la direccion de memoria de los 3 vertices que componen este triangulo
        std::list<Vertex>::iterator it_p;
        
        it_p = this->points.begin();
        std::advance(it_p,_p1);
        Vertex *v1 = &*it_p;
        
        it_p = this->points.begin();
        std::advance(it_p,_p2);
        Vertex *v2 = &*it_p;
        
        it_p = this->points.begin();
        std::advance(it_p,_p3);
        Vertex *v3 = &*it_p;

        /*
        Vertex *v1 = &this->points[_p1]; 
        Vertex *v2 = &this->points[_p2]; 
        Vertex *v3 = &this->points[_p3]; 
        */
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
    std::list<Vertex>::iterator p = this->points.begin();
    unsigned int pos = 0;
    while (p != this->points.end()) {
        std::cout<<"#"<<pos<<" "; p->print(); std::cout<<"\n";
        pos++;
        p++;
    }
    /*
    for (unsigned int i = 0; i < this->points.size(); i++) {
        std::cout<<"#"<<i<<" "; this->points[i].print(); std::cout<<"\n";
    }
    */
    std::cout<<"---------------------------------------------\n";

    std::cout<<"Triangulos:\n";
    
    //Impresion de triangulos
    std::list<Triangle>::iterator q = this->triangles.begin();
    unsigned int pos2 = 0;
    while (q != this->triangles.end()) {
        std::cout<<"#"<<pos2<<" "; q->print(true); std::cout<<"\n";
        pos2++;
        q++;
    }

   /*
    for (unsigned int i = 0; i < this->triangles.size(); i++) {
        std::cout<<"#"<<i<<" "; this->triangles[i].print(true);
    }
    */
}

//Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
bool Graph::deletePoint(Point &P) {      
    //Obtiene la posicion en el vector donde esta el vertex que representa a P
    int position = this->searchPoint(P);
    if (position == -1) 
        return false; //Point no encontrado
    else {
        std::cout<<"Se borrara el punto "<<position<<"\n"; 
        
        //Retriangula basado en la posicion de P
        std::list<Vertex>::iterator it = this->points.begin();
        std::advance(it, position);
        Vertex *point_to_triangulate = &*it;
        this->retriangulate(point_to_triangulate);
        //this->retriangulate(&points[position]);
        std::cout<<"\nSe pudo retriangular con exito\n";
        
        //Borra todos los enlaces de P con sus vecinos
        unsigned int count_of_deleted_neighbors = it->deleteAllNeighbors();
        //unsigned int count_of_deleted_neighbors = this->points[position].deleteAllNeighbors();
        std::cout<<"Se borraron "<<count_of_deleted_neighbors<<" vecinos del punto "; P.print(true);
        
        //Borra a P de la estructura
        //this->points.erase(this->points.begin()+position);
        this->points.erase(it);
        return true;
    }
}

//Dado un poligono, encuentra una diagonal valida y retorna sus indices por referencia
bool Graph::findValidDiagonal(std::vector<Vertex *> polygon, unsigned int &p1, unsigned int &p2) {
    unsigned int polysize = polygon.size();
    for (unsigned int i = 0; i < polysize; i++) {
        for (unsigned int j = i+1; j < polysize; j++) {
            if(utils::diagonalInsidePolygon(polygon, i, j)) {
                p1 = i;
                p2 = j;
                //std::cout<<"Se encontro la diagonal=\n"; polygon[p1]->print(); polygon[p2]->print();
                return true;
            }
        }
    }
    return false;
}


//Retriangula recursivamente
void Graph::retriangulate(std::vector<Vertex *> polygon) {
    if (polygon.size() <= 3) 
        return; //no hay mas diagonales validas
    unsigned int p1;
    unsigned int p2;
    //encuentra UNA diagonal valida para agregar
    if (this->findValidDiagonal(polygon, p1, p2)) {
        polygon[p1]->addNeighbor(polygon[p2]); //agrega un nuevo vecino
        
        std::vector<Vertex *> p1p2; //Polygono que va desde p1 a p2 CCW
        std::vector<Vertex *> p2p1; //Poligono que va desde p2 a p1 CCW
        std::cout<<"Se triangulara por la diagonal "; polygon[p1]->p.print(); std::cout<<" "; polygon[p2]->p.print(true); 
        //separar poligono en p1p2 y p2p1
        unsigned int index;
        index = p1;
        std::cout<<"p1-p2 = ";
        while (true) {
            p1p2.push_back(polygon[index]);
            
            polygon[index]->p.print();
            
            index++;
            if (index >= polygon.size())
                index = 0; //index empieza desde el principio
            if (index == p2) {
                p1p2.push_back(polygon[index]);
                polygon[index]->p.print();
                break;
            }
        }
        std::cout<<"\np2-p1 = ";
        index = p2;
        while (true) {
            p2p1.push_back(polygon[index]);
            
            polygon[index]->p.print();
            
            index++;
            if (index >= polygon.size())
                index = 0; //index empieza desde el principio
            if (index == p1) {
                p2p1.push_back(polygon[index]);
                polygon[index]->p.print();
                break;
            }
        }
        //Llamar recursivamente a retriangulate con cada mitad
        this->retriangulate(p1p2);
        this->retriangulate(p2p1);

    } else {
        std::cout<<"\nNo se encontro una diagonal valida para retriangular.\n\n";
    }

}

//Dado un vertice para borrar, genera nuevas vecindades
void Graph::retriangulate(Vertex *vertex_to_delete) {
    //Obtenemos todos los vecinos del vertice a borrar
    std::vector<Vertex *> neighbors_of_todelete = vertex_to_delete->neighbors;
    //retriangulamos
    this->retriangulate(neighbors_of_todelete);
}

//Dado un punto, busca el vertice que lo referencia. 
//Retorna el indice en el vector de vertices o -1 si nadie lo referencia (no se encontro)
int Graph::searchPoint(const Point &P) {
    int posi = 0;
    std::list<Vertex>::iterator it = this->points.begin();
    while(it != this->points.end()) {
        if (it->p == P)
            return posi;
        it++;
        posi++;
    }
    return -1;
    /*
    for (unsigned int i = 0; i < this->points.size(); i++) {
        if (this->points[i].p == P) {
            return i;
        }
    }
    return -1;
    */
}

void Graph::drawPoints() {
    glBegin(GL_POINTS);
    std::list<Vertex>::iterator it = this->points.begin();
    while(it != this->points.end()) {
        glVertex2f(it->p.x, it->p.y);
        it++;
    }
    /*
    for (unsigned int i = 0; i < this->points.size(); i++) {
        Vertex *v = &this->points[i];
        glVertex2f(v->p.x, v->p.y);
    }
    */
    glEnd();
}

void Graph::drawLines() {
    glBegin(GL_LINES);
    std::list<Vertex>::iterator v_it = this->points.begin();
    while (v_it != this->points.end()) {
        v_it->print();
        unsigned int cantidad_vecinos = v_it->neighbors.size();
        for (unsigned int j = 0; j < cantidad_vecinos; j++) {
            Vertex *u = v_it->neighbors[j];
            glVertex2f(v_it->p.x, v_it->p.y);
            glVertex2f(u->p.x, u->p.y);
        }
        v_it++;
    }
    /*  
    for (unsigned int i = 0; i < this->points.size(); i++) {
        Vertex *v = &this->points[i];
        v->print(); 
        unsigned int cantidad_vecinos = v->neighbors.size();
        for (unsigned int j = 0; j < cantidad_vecinos; j++) {
            Vertex *u = v->neighbors[j];
            glVertex2f(v->p.x, v->p.y);
            glVertex2f(u->p.x, u->p.y);
        }
    }*/
    glEnd();
}

//borra el vertice mas cercano a P
void Graph::deleteNearest(Point &P) {
    
    unsigned int nearest = 0;
    unsigned int pos = 0;
    float current_distance = utils::dist(P, this->points.front().p);
    std::list<Vertex>::iterator it = this->points.begin(); it++; //empieza desde le segundo valor
    while (it != this->points.end()) {
        float new_dist = utils::dist(P, it->p);
        if (new_dist < current_distance) {
            nearest = pos;
            current_distance = new_dist;
        } 
        pos++;
        it++;
    }
    std::list<Vertex>::iterator it_todelete = this->points.begin();
    std::advance(it_todelete, nearest);
    Point point_to_delete = it_todelete->p;
    this->deletePoint(point_to_delete);
    /* 
    for (unsigned int i = 1; i < this->points.size(); i++) {
        float new_dist = utils::dist(P, this->points[i].p);
        if (new_dist < current_distance) {
            nearest = i;
            current_distance = new_dist;
        }
    }
    this->deletePoint(this->points[nearest].p);
    */
}
