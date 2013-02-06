#include "Vertex.h"
#include "Point.h"
#include <vector>
#include <iostream>

//Constructor
Vertex::Vertex(float _x, float _y) {
    this->p.x = _x;
    this->p.y = _y;
    
}

//Devuelve la cantidad de vecinos que tiene
unsigned int Vertex::degree() {
    return this->neighbors.size();
}

//Agrega TODOS los vecinos a la lista de vecinos
void Vertex::setNeighbors(std::vector<Vertex *> _newneighbors) {
    if (this->degree() > 0) {
        std::cout<<"ERROR: ya se tienen vecinos. Borrando\n";
        this->neighbors.clear();
    }
    for (unsigned int i = 0; i < _newneighbors.size(); i++) {
        this->neighbors.push_back(_newneighbors[i]);
    }
}

//Agrega un vecino a la lista de vecinos
void Vertex::addNeighbor(Vertex *new_neighbor) {
    if (not isNeighbor(new_neighbor)) { //Si ya no esta en la lista de vecinos
        this->neighbors.push_back(new_neighbor); //Ahora son vecinos
        new_neighbor->addNeighbor(this);         //Que el otro me agregue como vecino tambien
    }
}

//Dado un vertice, se fija si es vecino
bool Vertex::isNeighbor(Vertex *neighbor) {
    int position = this->searchNeighbor(neighbor);
    if (position == -1 or position < this->neighbors.size()) 
        return false;//Fuera de rango => no es vecino
    else                
        return true; //En algun lado =>vecino
}

//Borra un vecino de la lista de vecinos. 
//Ademas, debe llamar a ese vecino para que lo borre al vertice actual de su lista
bool Vertex::deleteNeighbor(Vertex * neighbor) {
    if (this->isNeighbor(neighbor)) { //Si es vecino
        int position = this->searchNeighbor(neighbor);
        if (position == -1 or position < this->neighbors.size()) {
            return false; //Posicion no encontrada o fuera de rango
        } else {
            this->neighbors.erase(this->neighbors.begin()+position);
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
    for (unsigned int i = 0; i < this->neighbors.size(); i++) {
        bool deleted = this->neighbors[i]->deleteNeighbor(this);
        if (deleted)
            count++;
    }
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
