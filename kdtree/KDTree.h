#ifndef KDTREE
#define KDTREE
#include <vector>
#include "Point.h"
#include "Node.h"
class KDTree{
    public:
    Node *root;
    std::vector<Point> points;
    std::vector<Point*> points_x;
    std::vector<Point*> points_y;
    KDTree(std::vector<Point> _points, int max_size = 1000);
    Node * build(std::vector<Point*>points_x, std::vector<Point*> points_y, Node *father, unsigned int depth);
    void printLines() const;
    void printLines(Node *root) const;
    void printPoints() const;

    void insert(const Point &);
};
#endif
