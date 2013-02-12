#include "Vertex.h"
#include "Point.h"
#include "Triangle.h"
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
        std::cout<<"Llamando a new neighbor desde ";this->p.print(); std::cout<<" con "; new_neighbor->p.print(true);
        this->neighbors.push_back(new_neighbor); //Ahora son vecinos
        this->degree++;
        new_neighbor->addNeighbor(this);         //Que el otro me agregue como vecino tambien
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
        

//Recorre todos los vecinos y llama a deleteNeighbor. 
//Retorna la cantidad de vecinos borrados
unsigned int Vertex::deleteAllNeighbors() {
    unsigned int count = 0;
    while(this->neighbors.size()) {
        std::cout<<"Se borro el punto = "; this->neighbors.front()->p.print(); std::cout<<"\n";
        bool deleted = this->neighbors.front()->deleteNeighbor(this);
        if (deleted)
            count++;
    }
    /*
    for (unsigned int i = 0; i < this->neighbors.size(); i++) {
        bool deleted = this->neighbors[i]->deleteNeighbor(this);
        if (deleted)
            count++;
    }*/
    unsigned int new_degree = this->neighbors.size();
    if (new_degree > 0) {
        std::cout<<"Advertencia. No se borraron todos los vecinos\n";
    }
    std::cout<<this->degree<<' '<<new_degree<<' '<<count<<'\n';
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
