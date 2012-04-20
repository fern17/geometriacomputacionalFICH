#include <stack>
#include <list>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Point2D.h"

#define EPS 0.000001

//Variable global
Point2D minimal;

extern float anglePoint2D(Point2D & p1, Point2D & p2, bool comparar=true);
extern bool comparePoint2DMinimalLeftDown(Point2D & p1, Point2D & p2);
extern bool leftTurn(Point2D &p1, Point2D &p2, Point2D &p3);
extern void printList(std::list<Point2D> &Q);
extern void printStack(std::stack<Point2D> &S);
extern bool compareEqualFloat(float, float);
extern float modulo(Point2D & p1);

//Compara polarmente ambos angulos, devolviendo true si p1 esta a un angulo menor de minimal que p2
bool comparePoint2DPolar(Point2D & p1, Point2D &p2){
  Point2D op1 = p1 - minimal;
  Point2D op2 = p2 - minimal;
  float ang1 = atan2(op1.y, op1.x);
  float ang2 = atan2(op2.y, op2.x);
  return ang1 < ang2;
  //return (anglePoint2D(p1, minimal) >= anglePoint2D(p2, minimal));
}

//Devuelve true si los dos puntos tienen el mismo angulo con Point2D minimal, una variable global
bool compareEqualAngle(Point2D &p1, Point2D &p2){
  Point2D op1 = p1 - minimal;
  Point2D op2 = p2 - minimal;
  float ang1 = atan2(op1.y, op1.x);
  float ang2 = atan2(op2.y, op2.x);
  return compareEqualFloat(ang1, ang2);
 
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

//Busca en tiempo lineal el elemento minimal (en x e y) de la lista
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

//Borra el minimal de la lista
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

//Verifica si hay puntos colineales y los borra, dejando solo el mas lejano 
// (la lista debe venir ordenada en forma polar)
void eliminarColineales(std::list<Point2D> &Q){
  std::list<Point2D>::iterator p = Q.begin();
  std::list<Point2D>::iterator q = p;
  q++;
  while(p != Q.end() and q != Q.end()){
    while(p != Q.end() and q != Q.end() and compareEqualAngle(*p, *q)){
      float modp = modulo(*p);
      float modq = modulo(*q);
      if(modp < modq){
          p = Q.erase(p);
          q++;
      }
      else {
          q = Q.erase(q);
          p = q;
          q++;
      }
    }
    if(q == Q.end() or p == Q.end()) break;
    p++; q++;
  }
}


//Realiza el algoritmo de Graham de las 3 monedas para hallar el Convex Hull S de una lista de Puntos Q.
//Devuelve una Pila con el resultado clockwise.
void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S){
  minimal = encontrarMinimal(Q);                            //Encuentra el minimal izquierda abajo
 // std::cout<<"Minimal: "; minimal.print();
  
  borrarMinimal(Q, minimal);                                //Borra el minimal de la cola 

  Q.sort(comparePoint2DPolar);                              //Ordena en forma polar
  //std::cout<<"Lista ordenada\n"; printList(Q);
  
  eliminarColineales(Q);                                    //Hace limpieza de los puntos colineales, dejando el mas lejano
 
  
  //Ubica las 3 primeras monedas
  S.push(minimal);                                          //Agrega el primero que es el minimal
  
  //Agrega la segunda y tercera
  std::list<Point2D>::iterator it = Q.begin();              //Iterador para recorrer la Q
  for(unsigned int i = 0; i < 2 and it != Q.end(); i++, it++){
    S.push(*it);
  }
  
  //tamanio de Q
  unsigned int n = Q.size();

  //Loop de Graham Scan
  for(unsigned int i = 2; i < n and it != Q.end(); i++, it++){
    Point2D ntt = nextToTop(S);
    Point2D nt = top(S);
    Point2D p = *it;
    while(!leftTurn(ntt, nt, p) and (S.size() > 1)){        //Si no froman un giro a la izquierda y queda mas de un elemento en S
      // printStack(S);
      S.pop();                                              //Saco el tope de S
      ntt = nextToTop(S);                                   //Renuevo los valores y vuelvo a probar
      nt = top(S);
    }
    S.push(p);                                              //Agrego el elemento a S
  }
}

