#ifndef NODE
#define NODE
#include <cstdlib>
#include "Point.h"
class Node {
    public:
    enum {UP, DOWN, LEFT, RIGHT, N};
    
    Node *father;   //Puntero al padre de este nodo. Si no tiene padre, apunta a sí mismo
    Node *left;     //Puntero al hijo izquierdo o NULL
    Node *right;    //Puntero al hijo derecho o NULL
    Node * limits[4]; //Identifica los limites de la region representada por este nodo 
    Point *point;   //Punto que representa este Nodo
    bool vertical;  //True si es un nodo que separa el espacio en vertical. False si lo separa en horizontal

    //Constructor vacío. Genera todo en NULL.
    Node(){
        father = this;
        left = right = NULL;
        point = NULL;
        vertical = true;
        for(unsigned int i = 0; i < N; i++) limits[i] = this;
    }
    
    //Constructor que se le pasan todos los parametros
    Node(Node *father, Node *left, Node *right, Point *point, bool vertical):
        father(father),
        left(left),
        right(right),
        point(point),
        vertical(vertical) {
        for(unsigned int i = 0; i < N; i++) limits[i] = NULL;
    }
   
    //Funcion que convierte a este nodo en un separador y le crea los dos hijos (que uno es el nuevo punto pasado como parametro y el otro es este mismo punto).
    //Depende de qué lado esté, si este nodo se convierte en hijo derecho o izquierdo.
    void updateLimits(Point &new_point) {
        bool vertical = this->vertical;
        
        //Crea el nuevo nodo que se va a agregar
        Node *new_node = new Node(this, NULL, NULL, &new_point, not vertical);
        //Crea un nodo que es copia de mí
        Node *old_node = new Node(this, NULL, NULL, this->point, not vertical);
        
        //Le asigna a los hijos los mismos limites que el padre (que soy yo)
        for (unsigned int i = 0; i < N; i++) {
            new_node->limits[i] = this->limits[i];
            old_node->limits[i] = this->limits[i];
        }
        
        //Si el nuevo nodo es un divisor vertical
        if (new_node->vertical) {
            //Si el nuevo esta a la izquierda de mi
            if (new_node->point->x < point->x) {
                new_node->limits[RIGHT] = this; //Yo defino el limite derecho del nuevo
                old_node->limits[LEFT] = this;  //y tambien defino el limite izquierdo del viejo
                
                //Actualizo mis hijos:
                //  * el izquierdo es el nuevo nodo
                //  * el derecho es el nodo viejo
                this->left = new_node;
                this->right = old_node;
            }
            else {  //El nuevo esta a la derecha
                new_node->limits[LEFT] = this;  //Yo soy el limite izquierdo del nuevo
                old_node->limits[RIGHT] = this; //Y soy el limite derecho del viejo
                this->left = old_node;          //Mi hijo izquierdo es el viejo
                this->right = new_node;         //Mi hijo derecho es el nuevo
            }
        } else {//el nuevo nodo es un divisor horizontal
                    //Si el nuevo nodo esta arriba del actual
            if (new_node->point->y < point->y) {
                new_node->limits[DOWN] = this;  //Yo soy el limite inferior del nuevo       
                old_node->limits[UP] = this;    //Y soy el limite superior del viejo
                this->left = new_node;          //Mi hijo izquierdo es el nuevo, porque esta arriba mio
                this->right = old_node;         //Mi hijo derecho es el viejo, que esta abajo mio
            }
            else {  //El nuevo nodo esta abajo mio
                new_node->limits[UP] = this;    //Yo soy el limite superior del nuevo
                old_node->limits[DOWN] = this;  //Y soy el limite inferior del viejo
                this->left = old_node;          //El viejo esta arriba mio
                this->right = new_node;         //El nuevo esta abajo mio
            }
        }
    }
};
#endif
