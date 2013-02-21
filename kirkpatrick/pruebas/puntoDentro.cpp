/*
 * =====================================================================================
 *
 *       Filename:  puntoDentro.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/21/2013 01:48:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "utils.cpp"
#include "Point.h"

int main() {
    Point p1(1, 0.1);
    Point p2(2, 1.2);
    Point p3(0.2, 1);
    Point t(1,0.05);
    std::cout<<utils::pointInTriangle(t, p1, p2, p3);
    return 0;

}
