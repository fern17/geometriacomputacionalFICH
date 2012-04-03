#include <list>
#include "Point2D.h"
#include <utility>
#include <iostream>
extern float dist(Point2D &, Point2D &);
extern void printList(std::list<Point2D> &Q);

float distancePair(std::pair<Point2D, Point2D> &pair){
    return dist(pair.first, pair.second);
}

void farthestPair(std::list<Point2D> &Q, std::pair<Point2D, Point2D> &FP, float &maxDistance){
    printList(Q);
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
            currentDistance = distancePair(farthest);
            r = q; //r se guarda B
        }
        q++;
    }
    p++;
    while(p != Q.end()){
        Point2D C = *p;//C es ahora el que esta luego de A
        // Point2D D = *r; 
        //float distanceBC = dist(B, C);
        
        float distancePrev = dist(farthest.second, C);
        if(distancePrev > currentDistance){
            farthest.first = C; //reemplazo el first, que antes era A, por C
            currentDistance = distancePrev;
        }

        while(true){
            Point2D Dprev = *r;
            count++; //iteraciones Mas Mas
            r++;
            if(r == Q.end()) break;
            //if(r == Q.end()) r = Q.begin(); //muevo r al principio si me paso
            Point2D D = *r;
            float distanceCD = dist(C, D); //la distancia entre CD es mayor o igual que CB
            if(distanceCD < distancePrev){ //la distancia empieza a bajar, entonces el anterior era el mas lejano
                farthest.second = Dprev;
                currentDistance = distancePrev;
                break;
            } else {
                //farthest.first = C;
                farthest.second = D;
                currentDistance = distanceCD;
            }
        }
        p++;
    }
    FP = farthest;
    maxDistance = currentDistance;
    std::cout<<"Iteraciones hechas para encontrar Farthest Pair: "<<count<<std::endl; //
}
