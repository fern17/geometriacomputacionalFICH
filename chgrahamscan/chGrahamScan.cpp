#include <list>
#include <stack>
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
  std::cout<<"Pila resultado:\n";
  while(!ss.empty()){
    ss.top().print();
    ss.pop();
  }
}

extern void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S);

int main(){
//  std::list<Point2D> points;
  unsigned int n;
  
  while(std::cin>>n and n != 0){
    std::list<Point2D> Q;
    std::stack<Point2D> S;
    
    leer(Q, n);
    
    grahamScan(Q,S);
    printStack(S);
    
    std::cout<<"----------"<<std::endl;
  }
  return 0;
}
