#include <utility>
#include <list>
#include "Point2D.h"

extern float signedArea(Point2D &p1, Point2D &p2, Point2D &p3);
extern bool compareEqualFloat(float v1, float v2);

void antipodalPairs(std::list<Point2D> &Q, std::list<std::pair<Point2D, Point2D> > &pairs){
    std::list<Point2D>::iterator p = Q.begin(),
                                 q = Q.begin(),
                                 nextp, nextq,
                                 q0, p0 = Q.begin();
    pairs.clear();

    //si tengo pocos elementos
    if(Q.size() < 3){
        for(std::list<Point2D>::iterator pp = Q.begin(); pp != Q.end(); pp++){
            for( std::list<Point2D>:: iterator qq = pp; qq != Q.end(); ++qq){
                pairs.push_back(std::make_pair(*pp,*qq));
            }
        }
        return;
    }
    
    nextp = p;
    nextp++; //el siguiente de p
    
    q++; //q es el next de p
    nextq = q;
    nextq++; //el siguiente de q
//revisar
    while(nextq != Q.end() && (signedArea(*p, *nextp, *nextq) > signedArea(*p, *nextp, *q))){
        q = nextq;
        nextq++;
    }
    
    q0 = q;
//revisar si no va Q.end()
    while( q != p0){
        p = nextp;

        std::pair<Point2D,Point2D> pq = std::make_pair(*p,*q);
        pairs.push_back(pq);
       //bucle infinito 
        while(signedArea(*p, *nextp, *nextq) > signedArea(*p, *nextp, *q)){
            q = nextq;
            nextq++;
            if(q == Q.end())
                q = Q.begin();
   
            pq = std::make_pair(*p,*q);
            if(pq != std::make_pair(*q0, *p0))
                pairs.push_back(pq);
            else
                return;
        }
        
        if(compareEqualFloat( signedArea(*p, *nextp, *nextq), signedArea(*p, *nextp, *q))){
            if(pq != std::make_pair(*q0,Q.back()))
                pairs.push_back(std::make_pair(*p, *nextq));
            else
                pairs.push_back(std::make_pair(*nextp, *q));
        }
    }
}
