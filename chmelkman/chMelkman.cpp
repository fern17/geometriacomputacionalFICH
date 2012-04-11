#include <list>
#include <deque>
#include <utility>
#include "Point2D.h"
#include <iostream>
#include <fstream>

void printList(std::list<Point2D> &Q){
  std::list<Point2D>::iterator it = Q.begin();
  std::cout<<"Lista:\n";
  while(it != Q.end()){
    it->print();
    it++;
  }
}
void leer(std::list<Point2D> &Q, int n){
  for(unsigned int i = 0; i < n; i++){
    Point2D p;
    std::cin>>p.x;
    std::cin>>p.y;
    Q.push_back(p);
  }
  //printList(Q);
}

void printDeque(std::deque<Point2D> &S){
    std::cout<<"Deque:\n";
    for(unsigned int i = 0; i < S.size(); i++){
        S.at(i).print();
    }
    std::cout<<"\n";
}

extern void melkman(std::list<Point2D> & Q, std::deque<Point2D> & D);

int main(){
  unsigned int n;
  
  while(std::cin>>n and n != 0){
    std::list<Point2D> Q;
    std::deque<Point2D> D;
    leer(Q,n);
    
    printList(Q);
    std::cout<<"Melkman Algorithm:\n";
    melkman(Q,D);
    printDeque(D);

    std::cout<<"----------"<<std::endl;
  }
  return 0;
}
