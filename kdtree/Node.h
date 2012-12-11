#ifndef NODE
#define NODE

#include "Point.h"
class Node {
    public:
    Node *father;
    Node *left;
    Node *right;
    Point *point;
    bool vertical;

    Node(){}
    Node(Node *father, Node *left, Node *right, Point *point, bool vertical):
        father(father),
        left(left),
        right(right),
        point(point),
        vertical(vertical)
    {}
};
#endif
