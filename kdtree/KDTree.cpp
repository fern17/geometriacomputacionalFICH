#include "KDTree.h"
#include "Utils.h"
#include <algorithm>
#include <GL/glut.h>

KDTree::KDTree(std::vector<Point> _points, int max_size) {
    //Reserva espacio para no tener problemas de punteros. 
    this->points.reserve(max_size);
    this->points = _points;

    //Copia los puntos en dos vectores y los ordenada por cada coordenada
    std::vector<Point*> points_x;
    std::vector<Point*> points_y;
    for (unsigned int i = 0; i < _points.size(); i++){
        points_x.push_back(&points[i]);
        points_y.push_back(&points[i]);
    }
    sort(points_x.begin(), points_x.end(), Utils::sortPointsByX);
    sort(points_y.begin(), points_y.end(), Utils::sortPointsByY);

    //Caso en que no hay puntos, la raiz es un nodo vacio
    if(points.empty())
        this->root = new Node();
    else
        this->root = this->build(points_x, points_y, NULL, 0);  //construye el arbol
}


//Funcion recursiva que construye el arbol. Devuelve el puntero a la raiz.
Node * KDTree::build(std::vector<Point*>points_x, std::vector<Point*> points_y, Node *father, unsigned int depth) {
    Node * new_root = new Node();   //Nodo vacio
    if (points_x.size() == 1) {     //Si queda un solo elemento en el vector
        new_root->father = father;  
        new_root->point = points_x[0]; 
        if (depth % 2 == 0)
            new_root->vertical = true;
        else
            new_root->vertical = false;
        return new_root; //Retorna porque no tiene que lanzar ninguna recursion
    }
    
    std::vector<Point*> left_x;
    std::vector<Point*> left_y;
    std::vector<Point*> right_x;
    std::vector<Point*> right_y;

    unsigned int median_pos;
    
    if (depth % 2 == 0) { //linea vertical
        
        median_pos = points_x.size()/2; //Posicion donde esta el elemento de la mediana en X (los elementos ya vienen ordenados)
        
        //Separa en left_x y right_x los elementos que estan a la izquierda o a la derecha de la mediana (fijandose solo en su posicion en el vector)
        for (unsigned int i = 0; i < points_x.size(); i++) {
            if ( i < median_pos) 
                left_x.push_back(points_x[i]);
            else
                right_x.push_back(points_x[i]);
        }
        
        //En left_y pone los elementos que estan a la izquierda en X del elemento de la mediana. Sino los pone en right_y
        for (unsigned int i = 0; i < points_y.size(); i++) {
            if (points_y[i]->x < points_x[median_pos]->x)
                left_y.push_back(points_y[i]);
            else
                right_y.push_back(points_y[i]);
        }
        
        //El punto del nodo a generar es el punto que estaba en la mediana
        new_root->point = points_x[median_pos]; 
        new_root->vertical = true;

    } else { //linea horizontal
        
        median_pos = points_y.size()/2;
        
        //Separa los elementos que estan a la izquierda o a la derecha de la mediana, en el vector ordenado por Y.
        for (unsigned int i = 0; i < points_y.size(); i++) {
            if ( i < median_pos) 
                left_y.push_back(points_y[i]);
            else
                right_y.push_back(points_y[i]);
        }
        
        //Pone en left_x los elementos que estan arriba del elemento de la mediana en Y. Si no lo pone en right_x
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

//Wrapper
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

//Inserta un nuevo elemento en el arbol
void KDTree::insert(const Point &p){
    points.push_back(p);
    Node *candidate = this->search(p);
    candidate->updateLimits(points.back());
}

//Devuelve un puntero a Nodo donde el punto P deberia insertarse
//Se mueve en el arbol haciendo las comparaciones de si esta arriba o abajo, a la derecha o a la izquierda
Node *KDTree::search (const Point &p) const {
    Node * candidate = this->root;
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
    return candidate;
}
