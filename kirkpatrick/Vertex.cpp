#include "Vertex.h"
#include "Point.h"
#include "Triangle.h"
#include "utils.cpp" 
#include <vector>
#include <iostream>
//Constructor
Vertex::Vertex(float _x, float _y) {
    this->p.x = _x;
    this->p.y = _y;
    this->neighbors.clear();
    this->triangles.clear();
    this->degree = 0;
}

//imprime el punto, sus vecinos y triangulos
void Vertex::print() {
    std::cout<<"Punto = "; this->p.print(true);
    
    std::cout<<"Vecinos: \n";
    for (unsigned int i = 0; i < this->neighbors.size(); i++) {
        this->neighbors[i]->p.print(false); 
        std::cout<<" ";
    }
    std::cout<<"\n";

    std::cout<<"Triangulos: \n"; 
    for (unsigned int i = 0; i < this->triangles.size(); i++) {
        std::cout<<"t #"<<i<<" "; this->triangles[i]->print(true);
    }
}


//Agrega TODOS los vecinos a la lista de vecinos
void Vertex::setNeighbors(std::vector<Vertex *> _newneighbors) {
    if (this->degree > 0) {
        std::cout<<"ERROR: ya se tienen vecinos. Borrando\n";
        this->neighbors.clear();
    }
    for (unsigned int i = 0; i < _newneighbors.size(); i++) {
        this->neighbors.push_back(_newneighbors[i]);
    }
    this->degree = this->neighbors.size();
}

//Agrega un triangulo a la lista de triangulos
bool Vertex::addTriangle(Triangle * _newtriangle) {
    if (not isTriangle(_newtriangle)) { //si ya no lo habia agregado antes
        this->triangles.push_back(_newtriangle);
        return true;
    }
    else 
        return false;
}

//Retorna true si este vertice ya lo tiene como vecino al triangulo de argumento
bool Vertex::isTriangle(Triangle * _newtriangle) {
    for (unsigned int i = 0; i < this->triangles.size(); i++) {
        if (this->triangles[i] == _newtriangle) { //compara direcciones
            return true;
        }
    }
    return false;
}

//Agrega un vecino a la lista de vecinos
void Vertex::addNeighbor(Vertex *new_neighbor) {
    if (not isNeighbor(new_neighbor)) { //Si ya no esta en la lista de vecinos
        std::cout<<"Llamando a addNeighbor desde ";this->p.print(); std::cout<<" con "; new_neighbor->p.print(true);
        this->neighbors.push_back(new_neighbor); //Ahora son vecinos
        this->degree++;
        new_neighbor->addNeighbor(this);         //Que el otro me agregue como vecino tambien
    }
}

//Agrega un vecino a la lista de vecinos pero lo inserta en la posición angular necesaria para mantener la relación CCW
void Vertex::addNeighborCCW(Vertex *new_neighbor) {
    if (not isNeighbor(new_neighbor)) { //Si ya no esta en la lista de vecinos
        std::cout<<"Llamando a addNeighborCCW desde ";this->p.print(); std::cout<<" con "; new_neighbor->p.print(true);
        Point reference = this->p; //el punto de referencia va a ser yo mismo
        //calcula el angulo entre el punto que quiero agregar y el de referencia (yo mismo)
        float angle_with_nn = utils::angleVectors(reference, new_neighbor->p); 
        std::cout<<"angulo con nn = "<<angle_with_nn; 
        //Ahora buscara donde ubicarlo:
        // Para ello, busca dónde ubicar new_neighbor de manera que el vector de vecinos quede ordenado con respecto al angulo que forma con reference.
        // De esta manera, se mantiene la invariante de CCW
        unsigned int current_pos = 0;
        for (; current_pos < this->neighbors.size(); current_pos++) {
            Point current_point = this->neighbors[current_pos]->p;
            float current_angle = utils::angleVectors(reference, current_point);
            std::cout<<"\nangulo con current_pos ("<<current_pos<<") = "<<current_angle; 
            if (current_angle >= angle_with_nn ) { //si me pase del angulo, salgo
                break;
            }
        }
        std::cout<<"\n";
        //En current_pos quedo guardada la posicion donde insertarlo

        this->neighbors.insert(this->neighbors.begin()+current_pos, new_neighbor); //Ahora son vecinos en la posicion correcta
        this->degree++;
        new_neighbor->addNeighborCCW(this);         //Que el otro me agregue como vecino tambien
    }
}

//Dado un vertice, se fija si es vecino
bool Vertex::isNeighbor(Vertex *neighbor) {
    int position = this->searchNeighbor(neighbor);
    if (position == -1 or position >= this->neighbors.size()) 
        return false;//Fuera de rango => no es vecino
    else                
        return true; //En algun lado =>vecino
}

//Borra un vecino de la lista de vecinos. 
//Ademas, debe llamar a ese vecino para que lo borre al vertice actual de su lista
bool Vertex::deleteNeighbor(Vertex * neighbor) {
    if (this->isNeighbor(neighbor)) { //Si es vecino
        int position = this->searchNeighbor(neighbor);
        if (position == -1 or position >= this->neighbors.size()) {
            return false; //Posicion no encontrada o fuera de rango
        } else {
            this->neighbors.erase(this->neighbors.begin()+position);
            this->degree--;
            neighbor->deleteNeighbor(this);
            return true;
        }
    }
    else
        return false; //No son vecinos
}
//Dado un vertice, devuelve los indices en el array de triangulos donde se halla 
//un triangulo que tiene a this y related_to como lado
std::vector<unsigned int> Vertex::findTriangles(Vertex *related_to) {
    std::vector<unsigned int> ret_val; 
    for (unsigned int i = 0; i < this->triangles.size(); i++) {
        if (this->triangles[i]->isSegment(this, related_to))
            ret_val.push_back(i);
    }
    return ret_val;
}

//Le digo a mis vecinos que borre todos los triangulos que nos tienen como lado
void Vertex::deleteTriangles(Vertex *related_to) {
    //Captura todos los triangulos
    std::vector<unsigned int> triangles_to_delete = this->findTriangles(related_to);
    if (triangles_to_delete.empty() ) {
        std::cout<<"Advertencia: No se borró ningún triangulo que tenga como lado a "; this->p.print(); std::cout<<"->"; related_to->print();
    }
    //Recorre todos los indices a borrar y los borra en mi
    for (unsigned int pos = 0; pos < triangles_to_delete.size(); pos++) {
        this->triangles.erase(this->triangles.begin()+pos);
    }
    std::cout<<"Se borraron "<<triangles_to_delete.size()<<" triangulos de "; this->p.print(true);
    //Llama al vecino a que borre los triangulos tambien
    related_to->deleteTriangles(this);
}

//Recorre todos los vecinos y llama a deleteNeighbor. 
//Retorna la cantidad de vecinos borrados
unsigned int Vertex::deleteAllNeighbors() {
    unsigned int count = 0;
    while(this->neighbors.size()) {
        std::cout<<"Se borro el enlace con el punto = "; this->neighbors.front()->p.print(); std::cout<<'\n';
        //this->neighbors.front()->deleteTriangles(this);
        bool deleted = this->neighbors.front()->deleteNeighbor(this);
        if (deleted)
            count++;
    }
    unsigned int new_degree = this->neighbors.size();
    if (new_degree > 0) {
        std::cout<<"Advertencia. No se borraron todos los vecinos\n";
    }
    this->degree = new_degree;
    return count;
}

//Igualdad en terminos del punto que representan
bool Vertex::operator == (const Vertex &V) {
    return this->p == V.p;
}

//Dado un vecino, devuelve la posicion donde esta en el vector de vecinos
int Vertex::searchNeighbor(Vertex *V) {
    for (unsigned int i = 0; i < this->neighbors.size(); i++) {
        if (this->neighbors[i] == V) 
            return i;
    }
    return -1;
}
