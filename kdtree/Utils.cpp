#include "Utils.h"
#include "Point.h"
#include <fstream>
#include <string>
#include <vector>

bool Utils::sortPointsByX(const Point *P, const Point *Q) {
    return P->x < Q->x;
}

bool Utils::sortPointsByY(const Point *P, const Point *Q) {
    return P->y < Q->y;
}

std::vector<Point> Utils::readFile(std::string name) {
    std::vector<Point> ret_val;
    std::ifstream file (name.c_str());
    float x, y;
    while(file>>x>>y) {
        Point p(x,y);
        ret_val.push_back(p);
    }
    return ret_val;
}

Point* Utils::minimum(Point *a, Point *b, Point *c, bool vertical) {
    Point *ret_val;
    if (vertical == true) {
        if(a->x < b->x and a->x < c->x) 
            ret_val = a;
        else 
        if (b->x < a->x and b->x < c->x) 
            ret_val = b;
        else
            ret_val = c;
    }
    else {
        if(a->y < b->y and a->y < c->y) 
            ret_val = a;
        else 
        if (b->y < a->y and b->y < c->y) 
            ret_val = b;
        else
            ret_val = c;
    }
    return ret_val;
}
