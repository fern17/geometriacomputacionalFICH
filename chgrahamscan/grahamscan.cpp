#ifndef __GRAHAMSCAN_CPP__
#define __GRAHAMSCAN_CPP__

#include <stack>
#include <list>
#include <cmath>
#include "gcfunc.cpp"
#include <algorithm>

#define EPS 0.000001

//Variable global
Point2D minimal;


bool comparePoint2DPolar(Point2D & p1, Point2D &p2){
  return (anglePoint2D(p1, minimal) >= anglePoint2D(p2, minimal));
}

//Retorna el tope de la pila
Point2D top(std::stack<Point2D> &S){
  return S.top();
}

//Retorna el 2do elemento de la pila
Point2D nextToTop(std::stack<Point2D> &S){
  Point2D temp = S.top();     //Guarda temporalmente el valor de top
  S.pop();                  //Lo saca
  Point2D returnval = S.top();      //Almacena el valor a retornar
  S.push(temp);             //Vuelve a rearmar la pila original
  return returnval;
}

Point2D encontrarMinimal(std::list<Point2D> &Q){
  std::list<Point2D>::iterator it = Q.begin();
  Point2D minimo = *it;
  while(it != Q.end()){
    Point2D candidato = *it;
    if(comparePoint2DMinimalLeftDown(candidato, minimo)){
      minimo = candidato;
    }
    it++;
  }
  return minimo;
}

void borrarMinimal(std::list<Point2D> &Q, Point2D & minimo){
  std::list<Point2D>::iterator it = Q.begin();
  while(it != Q.end()){
    Point2D candidato = *it;
    if(candidato == minimo){
      Q.erase(it);
      break;
    }
    it++;
  }
}


//Realiza el algoritmo de Graham de las 3 monedas para hallar el Convex Hull S de una lista de Puntos Q.
void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S){
  
  minimal = encontrarMinimal(Q); //Encuentra el minimal izquierda abajo
  borrarMinimal(Q, minimal);//Borra el minimal de la cola 
  
  Q.sort(comparePoint2DPolar); //ordena en forma polar
  
  //Ubica las 3 primeras monedas
  S.push(minimal); //Agrega el primero que es el minimal
  
  //Agrega la segunda y tercera
  std::list<Point2D>::iterator it = Q.begin(); //Iterador para recorrer la Q
  for(unsigned int i = 0; i < 2 and it != Q.end(); i++, it++){
    S.push(*it);
  }

  //tamanio de Q
  unsigned int n = Q.size();

  for(unsigned int i = 3; i < n and it != Q.end(); i++, it++){
    Point2D ntt = nextToTop(S);
    Point2D nt = top(S);
    Point2D p = *it;
    while(!leftTurn(ntt, nt, p)){
      S.pop();
    }
    S.push(p);
  }
}

#endif
