#include "utils.cpp"
#include "Point.h"
#include <cmath>
int main() {
    Point p1(0,0);
    Point p2(-1,0);
    Point p3(-1,2);
    Point p4(-3,-1);
    Point p5(-1,-2);
    Point p6(2,-2);
    
    std::cout<<"con p2 = "<<utils::angleVectors(p1, p2);
    std::cout<<"\ncon p3 = "<<utils::angleVectors(p1, p3);
    std::cout<<"\ncon p4 = "<<utils::angleVectors(p1, p4);
    std::cout<<"\ncon p5 = "<<utils::angleVectors(p1, p5);
    std::cout<<"\ncon p6 = "<<utils::angleVectors(p1, p6);
    return 0;
}
