#include "grahamscan.cpp"
#include <list>
#include "Point2D.h"
#include <iostream>

void leer(std::list<Point2D> &Q, unsigned int n){
  for(unsigned int i = 0; i < n; i++){
    Point2D p;
    std::cin>>p.x;
    std::cin>>p.y;
    Q.push_back(p);
  }
}

void printStack(std::stack<Point2D> &S){
  std::stack<Point2D> ss(S);
  while(!ss.empty()){
    ss.top().print();
    ss.pop();
  }
}

int main(){
  std::list<Point2D> points;
  unsigned int n;
  
  while(std::cin>>n and n != 0){
    std::list<Point2D> Q;
    std::stack<Point2D> S;
    
    leer(points, n);
    
    grahamScan(Q,S);
    
    printStack(S);
  }
  return 0;
}
