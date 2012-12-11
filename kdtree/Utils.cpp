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
