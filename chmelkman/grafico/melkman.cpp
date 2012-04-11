#include <deque>
#include <list>
#include <iostream>
#include "Point2D.h"
#include <vector>


bool right(Point2D &A, Point2D &B, Point2D &C){
    float term1 = (B.x - A.x)*(C.y - A.y);
    float term2 = (C.x - A.x)*(B.y - A.y);
    return (term1 > term2);
}
//Realiza el algoritmo de Melkman para hallar el convex hull de un poligono simple
// La entrada Q debe ser un poligono simple ordenado 
void melkman(std::list<Point2D> & Q, std::deque<Point2D> & D){
    bool volar_b = false;
    bool volar_t = false;
    unsigned int m = 0;
    unsigned int b = 0;
    unsigned int t = 0;
    std::vector<Point2D> V;
    std::list<Point2D>::iterator p = Q.begin();
    while(p != Q.end()){
        V.push_back(*p);
        p++;
    }
    //Inicializa la deque con los primeros 3 en CCW
    if(right(V[0], V[1], V[2])){
        D.push_front(V[2]);
        D.push_front(V[1]);
        D.push_front(V[0]);
        D.push_front(V[2]);
    } else {
        D.push_front(V[2]);
        D.push_front(V[0]);
        D.push_front(V[1]);
        D.push_front(V[2]);
    }

    unsigned int n = Q.size();
    unsigned int i = 2;
    while((++i) < n){
        m = D.size();
        b = 0;
        t = D.size()-1;
        volar_b = right(V[i], D.at(b), D.at(b+1));
        volar_t = right(D.at(t-1), D.at(t), V[i]);
        
        if(!volar_b && !volar_t) //En el cono interno, no se agrega
            continue;

        while(volar_b){             
            D.pop_front();
            volar_b = right(V[i], D.at(b), D.at(b+1));
        }
        D.push_front(V[i]);//Dentro segun el primer segmento
        
        t = D.size()-1;
        volar_t = right(D.at(t-1), D.at(t), V[i]);
        while(volar_t){
            t--;
            D.pop_back();
            volar_t = right(D.at(t-1), D.at(t), V[i]);
        }
        D.push_back(V[i]); //Dentro segun el ultimo segmento
    }
}
