#ifndef NODE
#define NODE
#include <cstdlib>
#include "Point.h"
class Node {
    public:
    Node *father;
    Node *left;
    Node *right;
    Node * limits[4]; // {up, down, left, right}
    enum {UP, DOWN, LEFT, RIGHT, N};
    Point *point;
    bool vertical;

    Node(){
        father = this;
        left = right = NULL;
        point = NULL;
        vertical = true;
        for(unsigned int i = 0; i < N; i++) limits[i] = this;
    }
    Node(Node *father, Node *left, Node *right, Point *point, bool vertical):
        father(father),
        left(left),
        right(right),
        point(point),
        vertical(vertical)
    {
        for(unsigned int i = 0; i < N; i++) limits[i] = NULL;
    }
    
    void updateLimits(Point &new_point) {
        bool vertical = this->vertical;
        Node *new_node = new Node(this, NULL, NULL, &new_point, not vertical);
        Node *new_son = new Node(this, NULL, NULL, this->point, not vertical);
        
        for (unsigned int i = 0; i < N; i++) {
            new_node->limits[i] = this->limits[i];
            new_son->limits[i] = this->limits[i];
        }

        if (new_node->vertical) {
            if (new_node->point->x < point->x) {
                new_node->limits[RIGHT] = this;                
                new_son->limits[LEFT] = this;
                this->left = new_node;
                this->right = new_son;
            }
            else {
                new_node->limits[LEFT] = this;
                new_son->limits[RIGHT] = this;
                this->left = new_son;
                this->right = new_node;
            }
        } else {
            if (new_node->point->y < point->y) {
                new_node->limits[DOWN] = this;                
                new_son->limits[UP] = this;
                this->left = new_node;
                this->right = new_son;
            }
            else {
                new_node->limits[UP] = this;
                new_son->limits[DOWN] = this;
                this->left = new_son;
                this->right = new_node;
            }
        }
    }
};
#endif
