#include "Point.h"
#include <vector>
#include <string>
namespace Utils {
    bool sortPointsByX(const Point P, const Point Q);
    bool sortPointsByY(const Point P, const Point Q);
    std::vector<Point> readFile(std::string name);
    Point minimum(Point *a, Point *b, Point *c, bool vertical);
}
