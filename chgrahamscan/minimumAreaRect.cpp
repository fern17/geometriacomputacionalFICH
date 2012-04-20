#include <list>
#include "Point2D.h"
#include "Point3D.h"
#include <utility>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define PI 3.14159
#define INFINITO 10E12

extern bool compareEqualFloat(float v1, float v2);
extern float dotProduct(Point2D & p1, Point2D & p2);
extern float anglePoint2D(Point2D & p1, Point2D & p2, bool comparar);
extern float crossProduct(Point2D & p1, Point2D & p2);
extern float perpDist(float x1, float y1, float a2, float b2, float c2);

float perpDistWrapper(float x1, float y1, float x2, float y2, float slope){
    float a2 = -slope;
    float b2 = 1;
    float c2 = y1 - slope*x1;
    return perpDist(x1, y1, a2, b2, c2);
}
//devuelve el siguiente valor y MUEVE el indice
/*unsigned int next(unsigned int &idx, unsigned int n){
    if(idx+1 >= n){ 
        idx = 0;
        return 0;
    }
    else{
        idx++;
        return idx+1;
    }
}*/

//Calcula el angulo entre el vector ch[k-1]->ch[k] y ch[k]->ch[k+1]
// utilizando el producto punto: cos(tita) = (u.v)/(|u||v|)
float angle(std::vector<Point2D> &ch, unsigned int k){
    Point2D p1;
    p1.x = ch[k].x - ch[k-1].x;
    p1.y = ch[k].y - ch[k-1].y;
    //p1.print();

    Point2D p2;
    p2.x = ch[k+1].x - ch[k].x;
    p2.y = ch[k+1].y - ch[k].y;
    //p2.print();
    
    return anglePoint2D(p1,p2,false);
}

void minimumAreaRect(std::list<Point2D> & Q, float & area, Point2D & support, float & resultSlope){
    unsigned int n = Q.size();
    
    std::vector<Point2D> ch;
    std::list<Point2D>::iterator p = Q.begin();
    while(p != Q.end()){
        ch.push_back(*p);
        p++;
    }
    std::reverse(ch.begin(), ch.end());
    ch.push_back(Q.back());//agrego ultimo el primero, por las dudas que tengo que dar la vuelta
   
    unsigned int i = 0;
    unsigned int j = 1;
    unsigned int k = 1;
    unsigned int m = 1;
    unsigned int edge = 0;
    float d1 = 0.0;
    float d2 = 0.0;
    float slope = 0.0; //pendiente de la recta
    float At = INFINITO; //area soporte
    area = INFINITY; 
    float alfa = 0.0;
    float beta = angle(ch,1);
    float gamma = beta;
    float delta = beta;

        
    for(; i < n; i++){//notar que ch tiene size n+1 porque agregue el primer punto como ultimo, pero solo se va hasta n
        //std::cout<<"Iteracion="<<i<<'\n';
        if (i > 0){
            alfa += angle(ch, i);
        }

        while (beta < alfa + PI/2){
            j++;
            beta += angle(ch, j);
        }

        while (gamma < alfa + PI){
            k++;
            gamma += angle(ch, k);
        }
        
        while (delta < alfa + 3./2*PI){
            m++;
            delta += angle(ch, m);
        }
       
        //Calcula las distancias entre las lineas de soporte
        if (compareEqualFloat(ch[i+1].x, ch[i].x)){
            d1 = std::abs(ch[k].x - ch[i].x);
            d2 = std::abs(ch[m].y - ch[j].y);
        } 
        else if (compareEqualFloat(ch[i+1].y,ch[i].y)){
            d1 = std::abs(ch[k].y - ch[i].y);
            d2 = std::abs(ch[m].x - ch[j].x);
        }
        else {
            slope = (ch[i+1].y - ch[i].y)/(ch[i+1].x - ch[i].x);
            d1 = perpDistWrapper(ch[i].x, ch[i].y, ch[k].x, ch[k].y, slope);
            if(compareEqualFloat(slope, 0.0))    
                slope = 0.0001; //fix por si slope es casi como 0.
            
            d2 = perpDistWrapper(ch[j].x, ch[j].y, ch[m].x, ch[m].y, -1/slope);
        }
        
        //Calcula el area y reemplaza si es mas chica
        At = d1*d2;
        
        //std::cout<<i<<' '<<j<<' '<<k<<' '<<m<<'\n'<<d1<<' '<<d2<<' '<<At<<'\n';

        if ((i == 0) or ((At < area) and not compareEqualFloat(At,0.0))){
                area = At; //guarda el area resultado
                edge = i; // guarda el vertice resultado
                resultSlope = slope; //guarda la pendiente resultado
        }
    }
    support = ch[edge];
}

void minimumAreaRect2(std::list<Point2D> & Q, float & area, Point2D & support, float & resultSlope){
    unsigned int n = Q.size();
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int m = 0;
    unsigned int edge = 0;
    //Variables que marcan el siguiente, para el nodo final
    unsigned int nxti = 0;
    unsigned int nxtj = 0;
    unsigned int nxtk = 0;
    unsigned int nxtm = 0;
    float d1 = 0.0;
    float d2 = 0.0;
    float slope = 0.0; //pendiente de la recta
    float At = 0.0; //area soporte
    
    std::vector<Point2D> ch;
    std::list<Point2D>::iterator p = Q.begin();
    while(p != Q.end()){
        ch.push_back(*p);
        p++;
    }
    ch.push_back(Q.front());//agrego ultimo el primero, por las dudas que tengo que dar la vuelta
    std::reverse(ch.begin(), ch.end());
    
    for(; i < n; i++){
        Point2D ii1 = ch[i+1] - ch[i];;
        Point2D jj1 = ch[j+1] - ch[j];
        //Encuentra un vertice en la primer linea perpendicular de soporte
        while (dotProduct(ii1, jj1) > 0.0){
            j++;
            jj1 = ch[j+1] - ch[j];
        }
        

        if (i == 0) 
            k = j;
        //Encuentra un vertice en la linea paralela de soporte
        Point2D kk1 = ch[k+1] - ch[k];
        while (crossProduct(ii1, kk1) > 0.0){
            k++;
            kk1 = ch[k+1] - ch[k];
        }
        
        if (i == 0) 
            m = k;
        //Encuentra un vertice en la segunda linea perpendicular de soporte
        Point2D mm1 = ch[m+1] - ch[m];
        while (dotProduct(ii1, mm1) < 0.0){
            m++;
            mm1 = ch[m+1] - ch[m];
        }

        //Calcula las distancias entre las lineas de soporte
        if (ch[i+1].x == ch[i].x){
            d1 = std::abs(ch[k].x - ch[i].x);
            d2 = std::abs(ch[m].y - ch[j].y);
        } 
        else if (ch[i+1].y == ch[i].y){
            d1 = std::abs(ch[k].y - ch[i].y);
            d2 = std::abs(ch[m].x - ch[j].x);
        }
        else {
            slope = (ch[i+1].y - ch[i].y)/(ch[i+1].x - ch[i].x);
            d1 = perpDistWrapper(ch[i].x, ch[i].y, ch[k].x, ch[k].y, slope);
            if(compareEqualFloat(slope, 0.0))    
                slope = 0.0001; //fix por si slope es casi como 0.
            
            d2 = perpDistWrapper(ch[j].x, ch[j].y, ch[m].x, ch[m].y, -1/slope);
        }
        
        //Calcula el area y reemplaza si es mas chica
        At = d1*d2;
        
        if ((i == 0) or ((At < area) and not compareEqualFloat(At,0.0))){
                area = At; //guarda el area resultado
                edge = i; // guarda el vertice resultado
                resultSlope = slope; //guarda la pendiente resultado
        }
    }
    support = ch[edge];
}
