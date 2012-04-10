#include <list>
#include "Point2D.h"
#include <utility>
#include <iostream>
extern float dist(Point2D &, Point2D &);
extern void printList(std::list<Point2D> &Q);

float distancePair(std::pair<Point2D, Point2D> &pair){
    return dist(pair.first, pair.second);
}
//Calcula el par mas lejano en tiempo cuadratico, probando todos contra todos

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

//Calcula el par mas lejano en tiempo cuadratico, probando todos contra todos
//Guarda en maxDistance la distancia entre este par, que define el Diametro del poligono
void farthestPair(std::list<Point2D> &Q, std::pair<Point2D, Point2D> &FP, float &maxDistance){
    std::list<Point2D>::iterator p = Q.begin();
    std::list<Point2D>::iterator q = p;
    std::list<Point2D>::iterator r = p;
    
    int count = 0;                                  //cuenta la cantidad de iteraciones que hago en el algoritmo. Deberian ser maximo cN
    std::pair<Point2D, Point2D> farthest;
    
   //el par mas lejano inicial es la distancia entre p y p;
    farthest.first = *p;
    farthest.second = *p;     
    float currentDistance = 0.0;                    //inicializa en 0 la distancia
    
    Point2D A = *p;
    q++; 
    //encuentra el mas lejano de A
    while(q != Q.end()){                            //recorre todo y busca la distancia
        Point2D B = *q;
        float distanceAB = dist(A, B);
        if(distanceAB > currentDistance){
            farthest.second = B;
            currentDistance = distanceAB;
            r = q;                                  //r se guarda B
        }
        q++;
    }
    p++;                                            //muevo p porque tiene que empezar del siguiente
    while(p != Q.end()){
        Point2D C = *p;                             //C es ahora el que esta luego de A
        
        Point2D Dprev = *r;                         //me guardo el que era el mas lejano a A, o sea B

        float distancePrev = dist(Dprev, C);        //Esta es la nueva distancia, del siguiente a A (C), a B(Dprev)
        
        while(true){                                //loop infinito que termina cuando las distancias se empiezan a achicar en vez de agrandarse
            count++;                                //iteraciones Mas Mas
            
            r++;                                    //muevo r
            
            if(r == Q.end()) r = Q.begin();         //si r llego al final, lo vuelvo al principio para seguir buscando
            
            Point2D D = *r;

            float distanceCD = dist(C, D);          //la distancia entre CD es mayor o igual que CB
            
            if(distanceCD < distancePrev){          //la distancia empieza a bajar, entonces el anterior era el mas lejano
                r--;                                //r siempre tiene que quedar entre los dos mas lejanos
                break;                              //sale del while, ya tiene almacenado el mas lejano del vertice actual (C)
            } else 
                if(distanceCD > currentDistance){   //la distancia aumenta, entonces es un nuevo candidato a farthestPair
                farthest.first = C;                 //el first es C, que no varía en el while
                farthest.second = D;                //el second es D, que varía en cada iteracion del while
                distancePrev = distanceCD;          //distancia de comparacion
                currentDistance = distanceCD;       //distancia total
            } else {
                distancePrev = distanceCD;          //Si la distancia se mantuvo (??????), solo me importa la distancia nueva
            }
        }
        p++;                                        //muevo el pivote y vuelvo a buscar
    }
    
    FP = farthest;                                  //FP es el valor de retorno, un pair con ambos puntos
    maxDistance = currentDistance;                  //maxDistance es valor de retorno de la distancia, en float
    std::cout<<"Convex Hull Size: "<<Q.size()<<"\nIterations to find Farthest Pair: "<<count<<std::endl; //
}
