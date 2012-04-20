#include <cmath>
#include <iostream>

using namespace std;

float angle(float x1,float y1, float x2, float y2, float x3, float y3){
    float p1x = x1 - x2;
    float p1y = y1 - y2;
    float p2x = x3 - x2;
    float p2y = y3 - y2;
    float dotprod = p1x*p2x + p1y*p2y;
    float modp1 = sqrt(p1x*p1x + p1y*p1y);
    float modp2 = sqrt(p2x*p2x + p2y*p2y);
    return acos(dotprod/(modp1*modp2));
}

int main(){
    float x1 = -0.5;
    float y1 = 0.5;
    float x2 = 0;
    float y2 = 0;
    float x3 = 1;
    float y3 = 0;
    float a = angle(x1,y1,x2,y2,x3,y3);
    std::cout<<a<<' '<<a*180/3.1416<<std::endl;
    return 0;
}
