#include "Graph.h"
#include "utils.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <algorithm>

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

            std::list<Vertex>::iterator it_nn = this->points.begin(); 
            std::advance(it_nn, value);
            Vertex *new_neighbor = &*it_nn; //captura su direccion
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
    std::list<Vertex>::iterator it_tri = this->points.begin();
    while (it_tri != this->points.end()) {
        it->triangles.reserve(cantidad_triangulos);
        it_tri++;
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
    std::cout<<"---------------------------------------------\n";

    std::cout<<"Triangulos:\n";
    
    //Impresion de triangulos
    std::list<Triangle>::iterator q = this->triangles.begin();
    unsigned int pos2 = 0;
    while (q != this->triangles.end()) {
        std::cout<<"#"<<pos2<<" "; q->print(true); 
        pos2++;
        q++;
    }

}

void Graph::drawPoints() {
    glBegin(GL_POINTS);
    std::list<Vertex>::iterator it = this->points.begin();
    while(it != this->points.end()) {
        glVertex2f(it->p.x, it->p.y);
        it++;
    }
    glEnd();
}

void Graph::drawLines() {
    glBegin(GL_LINES);
    std::list<Vertex>::iterator v_it = this->points.begin();
    while (v_it != this->points.end()) {
        //v_it->print();
        unsigned int cantidad_vecinos = v_it->neighbors.size();
        for (unsigned int j = 0; j < cantidad_vecinos; j++) {
            Vertex *u = v_it->neighbors[j];
            glVertex2f(v_it->p.x, v_it->p.y);
            glVertex2f(u->p.x, u->p.y);
        }
        v_it++;
    }
    glEnd();
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
}

bool Graph::deletePoint(Point &P) {
    //Obtiene la posicion en el vector donde esta el vertex que representa a P
    int position = this->searchPoint(P);
    if (position == -1) 
        return false; //Point no encontrado
    else {
        std::cout<<"Se borrara el punto "<<position<<" = "; P.print(true);
        
        //Retriangula basado en la posicion de P
        std::list<Vertex>::iterator it = this->points.begin();
        std::advance(it, position);
        Vertex *point_to_triangulate = &*it;
        
        return this->deleteVertex(point_to_triangulate);
    }
}

//Borra un punto. Llama a retriangulate primero, y luego lo borra cuando nadie lo referencia
bool Graph::deleteVertex(Vertex *point_to_triangulate) {      
    std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\tSe borrara el punto = "; point_to_triangulate->p.print(true);
    std::cout<<"Comenzando retriangulacion.\n";
    this->retriangulate(point_to_triangulate);
    std::cout<<"\nTriangulacion finalizada.\n";

    //realiza una copia de los vecinos para borrar los triangulos luego
    std::vector<Vertex *> copy_of_neighbors = point_to_triangulate->neighbors;

    //Borrara todos los triangulos
    //Para cada vecino
    for (unsigned int i = 0; i < copy_of_neighbors.size(); i++) {
       //Para cada triangulo
       std::list<Triangle>::iterator t_it = this->triangles.begin();
       while (t_it != this->triangles.end() ) {
           Triangle tri = *t_it;
           if(tri.isSegment(point_to_triangulate, copy_of_neighbors[i])) {//si it y i forman el lado del triangulo j
               //debe borrar el triangulo de la lista de todos los vertices
               //it->deleteTriangles(copy_of_neighbors[i]);
               //copy_of_neighbors[i]->deleteTriangles(&*it);
               t_it->deleteAllPoints();
               t_it = this->triangles.erase(t_it);
           }
           else 
               t_it++;
       }
    }

    //Borra todos los enlaces de P con sus vecinos
    unsigned int count_of_deleted_neighbors = point_to_triangulate->deleteAllNeighbors();
    std::cout<<"Se borraron "<<count_of_deleted_neighbors<<" vecinos del punto "; point_to_triangulate->p.print(true);

    //Borra al punto de la estructura
    this->points.remove(*point_to_triangulate);
    //this->points.erase(it);
    return true;
}

//Dado un vertice para borrar, genera nuevas vecindades
void Graph::retriangulate(Vertex *vertex_to_delete) {
    //Obtenemos todos los vecinos del vertice a borrar
    std::vector<Vertex *> neighbors_of_todelete = vertex_to_delete->neighbors;
    //retriangulamos
    this->retriangulate(neighbors_of_todelete);
}

//Retriangula recursivamente
void Graph::retriangulate(std::vector<Vertex *> polygon) {
    unsigned int polysize = polygon.size();
    if (polysize < 3) 
        return; //no hay mas diagonales validas
    if (polysize == 3) { //aca tengo un triangulo, debo agregarlo a la lista de triangulos de los vertices
        Vertex *tp1 = polygon[0];
        Vertex *tp2 = polygon[1];
        Vertex *tp3 = polygon[2];
        Triangle tri(tp1, tp2, tp3);
        
        this->triangles.push_back(tri);
        Triangle *ptri = &this->triangles.back();

        std::cout<<"Se agrega el triangulo "; ptri->print(true);
        
        tp1->triangles.push_back(ptri);
        tp2->triangles.push_back(ptri);
        tp3->triangles.push_back(ptri);
        return;
    }

    unsigned int p1;
    unsigned int p2;
    //encuentra UNA diagonal valida para agregar
    if (this->findValidDiagonal(polygon, p1, p2)) {
        std::cout<<"Se triangulara por la diagonal "; polygon[p1]->p.print(); std::cout<<" "; polygon[p2]->p.print(true); 
        polygon[p1]->addNeighborCCW(polygon[p2]); //agrega un nuevo vecino
        
        std::vector<Vertex *> p1p2; //Polygono que va desde p1 a p2 CCW
        std::vector<Vertex *> p2p1; //Poligono que va desde p2 a p1 CCW
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
        std::cout<<"\n";
        //Llamar recursivamente a retriangulate con cada mitad
        this->retriangulate(p1p2);
        this->retriangulate(p2p1);

    } else {
        std::cout<<"\nNo se encontro una diagonal valida para retriangular.\n\n";
    }

}

//Dado un poligono, encuentra una diagonal valida y retorna sus indices por referencia
bool Graph::findValidDiagonal(std::vector<Vertex *> polygon, unsigned int &p1, unsigned int &p2) {
    std::cout<<"Poligono = ";
    for(unsigned int i = 0; i < polygon.size(); i++) 
        polygon[i]->p.print(false);
    std::cout<<"\n";
    
    unsigned int polysize = polygon.size();
    for (unsigned int i = 0; i < polysize; i++) {
        for (unsigned int j = i+2; j < polysize; j++) {
            //std::cout<<"Probando con ";
            //polygon[i]->p.print(); polygon[j]->p.print();
            if(utils::diagonalInsidePolygon(polygon, i, j)) {
                p1 = i;
                p2 = j;
                std::cout<<"Se encontro la diagonal="<<i<<' '<<j<<'\n'; polygon[p1]->print(); polygon[p2]->print();
                return true;
            }
        }
    }
    return false;
}

//borra el vertice mas cercano a P
void Graph::deleteNearest(Point &P) {
    std::cout<<"\n\n\n\n\n"; 
    unsigned int nearest = 0;
    unsigned int pos = 0;
    float current_distance = utils::dist(P, this->points.front().p);
    std::list<Vertex>::iterator it = this->points.begin(); it++; //empieza desde el segundo valor
    Point point_to_delete;
    while (it != this->points.end()) {
        float new_dist = utils::dist(P, it->p);
        if (new_dist < current_distance) {
            nearest = pos;
            current_distance = new_dist;
            point_to_delete = it->p;
        } 
        pos++;
        it++;
    }
    
    this->deletePoint(point_to_delete);
}


std::vector<Vertex *> Graph::selectVertexToDelete(unsigned int max_degree) {
    unsigned int marked_vertex = 0;
    unsigned int pointsize = this->points.size();
    //Primero marcamos todos los que tienen mayor al grado designado
    std::list<Vertex>::iterator p = this->points.begin();
    while (p != this->points.end()) {
        Vertex *current = &*p;
        if (current->degree > max_degree) {//si supera el grado, lo marcamos
            current->mark();  //lo marcamos
            marked_vertex++;  //aumentamos el contador
        }
        p++;
    }
    //en vertex_to_delete guardaremos los vertices que vamos a borrar
    std::vector<Vertex *> vertex_to_delete;
    p = this->points.begin();
    //marcamos los primeros 3 puntos que seran los que nunca se deben borrar
    for (int i = 0; i < 3; i++) {
        p->mark();
        p++;
    }
    while (marked_vertex != pointsize) {
        while ((p != this->points.end()) and (p->isMarked()))
            p++;
        if (p == this->points.end())
            break;
        p->mark();
        marked_vertex++;
        vertex_to_delete.push_back(&*p);

        //Obtenemos sus vecinos
        std::vector<Vertex *> neighbors_to_mark = p->neighbors;
        //Marcamos todos sus vecinos
        for (unsigned int j = 0; j < neighbors_to_mark.size(); j++) {
            neighbors_to_mark[j]->mark();
            marked_vertex++;
        }
    }
   
    //Antes de salir, desmarcamos todos
    unmarkAllVertex();

    return vertex_to_delete;
}

void Graph::unmarkAllVertex() {
    std::list<Vertex>::iterator p = this->points.begin();
    while (p != this->points.end()) {
        p->unmark();
        p++;
    }
}
