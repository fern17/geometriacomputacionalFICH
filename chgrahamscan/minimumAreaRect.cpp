#include <list>
#include "Point2D.h"
#include "Point3D.h"
#include <utility>
#include <iostream>

extern float dist(Point2D &, Point2D &);
extern void printList(std::list<Point2D> &Q);


unsigned int next(unsigned int idx, unsigned int n){
    if(idx+1 == n) 
        return 0;
    else
        return idx+1;
}

void minimunAreaRect(std::list<Point2D> & Q, float & area, Point2D & support, float & resultSlope){
    unsigned int n = Q.size();
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int m = 0;
    //Variables que marcan el siguiente, para el nodo final
    unsigned int nxti = 0;
    unsigned int nxtj = 0;
    unsigned int nxtk = 0;
    unsigned int nxtm = 0;
    float d1 = 0.0;
    float d2 = 0.0;
    float slope = 0.0; //pendiente de la recta
    float At = 0.0; //area soporte
    
    std::vector<Point2D> ch = Q;

    for(; i < n; i++){
        
        Point2D ii1 = ch[next(i,n)] - ch[i];;
        Point2D jj1 = ch[next(j,n)] - ch[j];

        while (dotProduct(ii1, jj1) > 0.0){
            j++;
            jj1 = ch[next(j,n)] - ch[j];
        }
        

        if (i == 1) 
            k = j;

        Point2D kk1 = ch[next(k,n)] - ch[k];
        while (crossProduct(ii1, kk1) > 0.0){
            k++;
            kk1 = ch[next(k,n)] - ch[k];
        }
        
        if (i == 1) 
            m = k;

        Point2D mm1 = ch[next(m,n)] - ch[m];
        while (dotProduct(ii1, mm1) < 0.0){
            m++;
            mm1 = ch[next(m,n)] - ch[m];
        }

        if (ch[next(i,n)].x == ch[i].x){
            d1 = abs(ch[k].x - ch[i].x);
            d2 = abs(ch[m].y - ch[j].y);
        } 
        else if (ch[next(i,n)].y == ch[i].y){
            d1 = abs(ch[k].y - ch[i].y);
            d2 = abs(ch[m].x - ch[j].x);
        }
        else {
            slope = (ch[next(i,n)].y - ch[i].y)/(ch[next(i,n)].x - ch[i].x);
            d1 = perpDist(ch[i].x, ch[i].y, ch[k].x, ch[k].y, slope);

            if(compareEqualFloat(slope, 0.0))    
                slope = 0.0001; //fix por si slope es casi como 0.
            
            d2 = perpDist(ch[j].x, ch[j].y, ch[m].x, ch[m].y, -1/slope);
        }
        
        At = d1*d2;
        if ((i == 1) or (At < area)){
                area = At; //guarda el area resultado
                edge = i; // guarda el vertice resultado
                resultSlope = slope; //guarda la pendiente resultado
        }
    }
    support = ch[next(edge,n)] - ch[edge];
}
