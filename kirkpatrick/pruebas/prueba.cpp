#include "Point.h"
#include "utils.cpp"
#include <vector>
#include <iostream>

std::vector<Point> polygon;
void probar(unsigned int _p1, unsigned int _p2) {
    Point p1 = polygon[_p1];
    Point p2 = polygon[_p2];
    std::cout<<utils::diagonalInsidePolygon(polygon, p1, p2)<<"\n\n\n";
}


int main(int argc, char **argv) {
    utils::loadPoints("points2.txt", polygon);
    std::cout<<"\n\n\n";
    probar(0,1);
    probar(0,6);
    probar(0,5);
    probar(0,4);
    probar(3,5);
    probar(3,1);
    probar(5,1);
    return 0;
    
}
