#include "KDTree.h"
#include "Utils.h"
#include <algorithm>
#include <GL/glut.h>

KDTree::KDTree(std::vector<Point> _points, int max_size) {
    this->points.reserve(max_size);
    this->points = _points;
    std::vector<Point*> points_x;
    std::vector<Point*> points_y;
    for (unsigned int i = 0; i < _points.size(); i++){
        points_x.push_back(&points[i]);
        points_y.push_back(&points[i]);
    }
    sort(points_x.begin(), points_x.end(), Utils::sortPointsByX);
    sort(points_y.begin(), points_y.end(), Utils::sortPointsByY);
    this->root = this->build(points_x, points_y, NULL, 0); 
}

Node * KDTree::build(std::vector<Point*>points_x, std::vector<Point*> points_y, Node *father, unsigned int depth) {
    Node * new_root = new Node();
    if (points_x.size() == 1) {
        new_root->father = father;
        new_root->point = points_x[0];
        if (depth % 2 == 0)
            new_root->vertical = true;
        else
            new_root->vertical = false;
        return new_root;
    }
    
    std::vector<Point*> left_x;
    std::vector<Point*> left_y;
    std::vector<Point*> right_x;
    std::vector<Point*> right_y;

    unsigned int median_pos;
    if (depth % 2 == 0) { //linea vertical
        median_pos = points_x.size()/2;
        for (unsigned int i = 0; i < points_x.size(); i++) {
            if ( i < median_pos) 
                left_x.push_back(points_x[i]);
            else
                right_x.push_back(points_x[i]);
        }
        for (unsigned int i = 0; i < points_y.size(); i++) {
            if (points_y[i]->x < points_x[median_pos]->x)
                left_y.push_back(points_y[i]);
            else
                right_y.push_back(points_y[i]);
        }
        
        new_root->point = points_x[median_pos]; 
        new_root->vertical = true;

    } else { //linea horizontal
        median_pos = points_y.size()/2;
        for (unsigned int i = 0; i < points_y.size(); i++) {
            if ( i < median_pos) 
                left_y.push_back(points_y[i]);
            else
                right_y.push_back(points_y[i]);
        }
        for (unsigned int i = 0; i < points_x.size(); i++) {
            if (points_x[i]->y < points_y[median_pos]->y)
                left_x.push_back(points_x[i]);
            else
                right_x.push_back(points_x[i]);
        }
        
        new_root->point = points_y[median_pos]; 
        new_root->vertical = false;
    }
    new_root->father = father;
    new_root->left = this->build(left_x, left_y, new_root, depth+1);
    new_root->right = this->build(right_x, right_y, new_root, depth+1);
    return new_root;

}

void KDTree::printPoints() const {
    for (unsigned int i = 0; i < this->points.size(); i++) {
        glVertex2f(this->points[i].x, this->points[i].y);
    }
}

void KDTree::printLines() const {
    this->printLines(this->root);
}

void KDTree::printLines(Node *root) const {
    if(root->left == NULL or root->right == NULL) return;

    if (root->vertical) {
        glVertex2f(root->point->x, 0); 
        glVertex2f(root->point->x, 480);  
    } else {
        glVertex2f(0, root->point->y); 
        glVertex2f(640, root->point->y);  
    }
    printLines(root->left);
    printLines(root->right);
}

void KDTree::insert(const Point &p){
    points.push_back(p);
    Node *candidate = root;
    bool vertical = true;
    while(candidate->left and candidate->right){
        if(vertical){
            if(candidate->point->x < p.x)
                candidate = candidate->right;
            else
                candidate = candidate->left;
        }
        else{
            if(candidate->point->y < p.y)
                candidate = candidate->right;
            else
                candidate = candidate->left;
        }
        vertical = not vertical; 
    }

    //tengo el padre
    Node *father = candidate;
    if(vertical){
        if(candidate->point->x < p.x){
            candidate->left = new Node(father, NULL, NULL, candidate->point, not vertical);
            candidate->right = new Node(father, NULL, NULL, &points.back(), not vertical);
        }
        else{
            candidate->left = new Node(father, NULL, NULL, &points.back(), not vertical);
            candidate->right = new Node(father, NULL, NULL, candidate->point, not vertical);
            candidate->point = &points.back();
        }
    }
    else{
        if(candidate->point->y < p.y){
            candidate->left = new Node(father, NULL, NULL, candidate->point, not vertical);
            candidate->right = new Node(father, NULL, NULL, &points.back(), not vertical);
        }
        else{
            candidate->left = new Node(father, NULL, NULL, &points.back(), not vertical);
            candidate->right = new Node(father, NULL, NULL, candidate->point, not vertical);
            candidate->point = &points.back();
        }
    }
}

