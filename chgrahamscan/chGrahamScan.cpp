#include <list>
#include <stack>
#include <utility>
#include "Point2D.h"
#include <iostream>


void printList(std::list<Point2D> &Q){
  std::list<Point2D>::iterator it = Q.begin();
  std::cout<<"Lista:\n";
  while(it != Q.end()){
    it->print();
    it++;
  }
}
void leer(std::list<Point2D> &Q, unsigned int n){
  for(unsigned int i = 0; i < n; i++){
    Point2D p;
    std::cin>>p.x;
    std::cin>>p.y;
    Q.push_back(p);
  }
  //printList(Q);
}



void printStack(std::stack<Point2D> &S){
  std::stack<Point2D> ss(S);
  std::cout<<"Pila:\n";
  while(!ss.empty()){
    ss.top().print();
    ss.pop();
  }
}

extern void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S);
extern void farthestPair(std::list<Point2D> & Q, std::pair<Point2D, Point2D> & FP, float & maxDistance);
extern void minimumAreaRect(std::list<Point2D> & Q, float & area, Point2D & support, float & resultSlope);

int main(){
//  std::list<Point2D> points;
  unsigned int n;
  
  while(std::cin>>n and n != 0){
    std::list<Point2D> Q;
    std::stack<Point2D> S;

    leer(Q, n);
    
    std::cout<<"Graham Scan:\n";
    grahamScan(Q,S);
    printStack(S);
   
    std::cout<<"Farthest Pair:\n";
    std::stack<Point2D> ss(S);
    std::list<Point2D> listaS;
    while(!ss.empty()){
        listaS.push_back(ss.top());
        ss.pop();
    }
    
    std::pair<Point2D, Point2D> fPair;
    float maxDist;
    farthestPair(listaS, fPair, maxDist);
    std::cout<<"Distance of Farthest Pair: "<<maxDist<<"\n";
    
    
    std::cout<<"Minimum Area Enclosing Rectangle:\n";
    float area = 0.0;
    float resultSlope = 0.0;
    Point2D soporte;
    
    minimumAreaRect(listaS, area, soporte, resultSlope);
    
    std::cout<<"Area: "<<area<<"\nPendiente: "<<resultSlope<<"\nAnclada en: ";
    soporte.print();

    std::cout<<"----------"<<std::endl;
  }
  return 0;
}
