#include <list>
#include "Point2D.h"
#include <utility>
#include <iostream>
extern float dist(Point2D &, Point2D &);
extern void printList(std::list<Point2D> &Q);

float distancePair(std::pair<Point2D, Point2D> &pair){
    return dist(pair.first, pair.second);
}

void farthestn2(std::list<Point2D> &Q, std::pair<Point2D, Point2D> &FP, float &maxDistance){
   std::list<Point2D>::iterator p = Q.begin();
   std::list<Point2D>::iterator q = p;
   q++;
   std::pair<Point2D, Point2D> farthest;
   farthest.first = *p;
   farthest.second = *q;
   float currentDistance = distancePair(farthest);
   while(p != Q.end()){
       q = p;
       q++;
       while(q != Q.end()){
           float distance = dist(*p, *q);
           if(distance > currentDistance){
               currentDistance = distance;
               farthest.first = *p;
               farthest.second = *q;
           }
           q++;
       }
       p++;
   }
    FP = farthest;
    maxDistance = currentDistance;
}


void farthestPair(std::list<Point2D> &Q, std::pair<Point2D, Point2D> &FP, float &maxDistance){
    std::list<Point2D>::iterator p = Q.begin();
    std::list<Point2D>::iterator q = p;
    std::list<Point2D>::iterator r = p;
    
    int count = 0; //cuenta la cantidad de iteraciones que hago en el algoritmo. Deberian ser maximo cN
    std::pair<Point2D, Point2D> farthest;
    
    farthest.first = *p;
    farthest.second = *p; //el par mas lejano inicial es la distancia entre p y p;
    float currentDistance = 0.0; //inicializa en 0 la distancia
    
    Point2D A = *p;
    q++; 
    //encuentra el mas lejano de A
    while(q != Q.end()){ //recorre todo y busca la distancia
        Point2D B = *q;
        float distanceAB = dist(A, B);
        if(distanceAB > currentDistance){
            farthest.second = B;
            currentDistance = distanceAB;
            r = q; //r se guarda B
        }
        q++;
    }
    p++;
    while(p != Q.end()){
        Point2D C = *p;//C es ahora el que esta luego de A
        
        Point2D Dprev = *r;

        float distancePrev = dist(Dprev, C);
        
        while(true){
            count++; //iteraciones Mas Mas
            
            r++;
            
            if(r == Q.end()) r = Q.begin();
            
            Point2D D = *r;

            float distanceCD = dist(C, D); //la distancia entre CD es mayor o igual que CB
            
            if(distanceCD < distancePrev){ //la distancia empieza a bajar, entonces el anterior era el mas lejano
                //currentDistance = distancePrev;
                r--;
                break;
            } else if(distanceCD > currentDistance){
                farthest.first = C;
                farthest.second = D;
                distancePrev = distanceCD;
                currentDistance = distanceCD;
            } else {
                distancePrev = distanceCD;
            }
        }
        p++;
    }
    
    FP = farthest;
    maxDistance = currentDistance;
    std::cout<<"Tamanio del Convex Hull: "<<Q.size()<<"\nIteraciones hechas para encontrar Farthest Pair: "<<count<<std::endl; //
}
