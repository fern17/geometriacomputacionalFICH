#ifndef KDTREE
#define KDTREE
#include <vector>
#include "Point.h"
#include "Node.h"
class KDTree{
    public:
    Node *root; //Puntero a la raiz del arbol
    //std::vector<Point> points;  //Vector que almacena las coordenadas de cada punto
    KDTree(std::vector<Point> _points, int max_size = 1000); //Constructor que le pasamos los puntos y un limite superior de la cantidad de puntos a almacenar
    Node * build(std::vector<Point>points_x, std::vector<Point> points_y, Node *father, unsigned int depth);
    void printLines() const;
    void printLines(Node *root) const;
    void printPoints(Node *root) const;
    void printPoints() const;
    void print();
    void print(Node * candidate, unsigned int depth);

    Node *search (const Point p) const;
    void insert(const Point );
    Point findMin(bool searchVertical);
    Point findMin(Node *node, bool searchVertical, bool vertical);
    Node* remove();
    Node* remove(Point p);
    Node* remove2(Node *node, Point p, bool vertical);
    Node* remove(Node *node, Point p, bool vertical);
    bool empty();
};
#endif
