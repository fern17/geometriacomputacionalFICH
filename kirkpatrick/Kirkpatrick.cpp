#include "Kirkpatrick.h"
#include "utils.cpp"
#include <iostream>

Kirkpatrick::Kirkpatrick() {
    this->root = NULL;
}


void Kirkpatrick::build(Graph *G, unsigned int max_degree) {
    if (G->size() < 3) {
        std::cout<<"No se pudo construir el DAG porque no se tienen suficientes puntos\n";
        return;
    }
    std::cout<<"Construyendo estructura de Kirkpatrick\n";
    //Primero se crea el nodo raiz con el triangulo envolvente
    TriangleStatic rootie = G->getBoundingTriangle();
    Node * root_node = new Node(rootie, NULL);
    this->root = root_node;
    std::vector<Node *> nodes_prev; //en este vector se almacenaran los nodos que se agregan en cada nivel del arbol, para iterar en el nivel siguiente
    //Ahora se agregan como hijos de la raiz, nodos formados por cada uno de los triangulos

    std::list<Triangle>::iterator i = G->triangles.begin();
    while (i != G->triangles.end()) {
        //Se crea un triangulo estatico a partir de uno dinamico
        TriangleStatic tri = TriangleStatic::buildFromTriangle(*i);
        Node *to_add = new Node(tri, this->root);
        //Y se agrega como hijo
        this->root->addChild(to_add);
        nodes_prev.push_back(to_add);
        i++;
    }

    //A continuacion, se debe iterar, borrar puntos y cambiar los padres de cada triangulo
    unsigned int niveles = 1;
    while (true) {
        //probar si se pueden borrar puntos
        if (G->size() <= 3) {
            std::cout<<"Ya no se pueden borrar más puntos, terminando la construccion de la estructura de Kirkpatrick\n";
            break;
        }
        //borrar puntos
        unsigned int cantidad_borrados = G->kirkpatrickDeletion(max_degree);
        std::cout<<"Se borraron "<<cantidad_borrados<<" puntos del grafo.\n";
        if (cantidad_borrados == 0) break; //ya no se pueden borrar más

        std::vector<Node *> new_nodes_prev; //vector que almacena los nodos del nivel Ti-1

        std::list<Triangle>::iterator k = G->triangles.begin();
        //Para cada triangulo en graph, ver con cuales se solapa de todos los triangulos del nivel anterior, y marcarlo como padredd
        while (k != G->triangles.end()) {
            Node *newNode = new Node(TriangleStatic::buildFromTriangle(*k), NULL); //se crea un nuevo nodo sin padre
            for (unsigned int j = 0; j < nodes_prev.size(); j++) {
                Node *current = nodes_prev[j];
                //si se superpone k con j, k es padre de j
                if (utils::triangleOverlap( TriangleStatic::buildFromTriangle(*k), 
                                            *current->triangle)) {
                    Node *old_father = current->father; //antiguo padre de j
                    old_father->deleteChild(current);   //j ya no es hijo de su antiguo padre
                    old_father->addChild(newNode);       //le agrego al padre el hijo nuevo
                    newNode->setFather(newNode);        //se le actualiza el padre al nodo actual
                    newNode->addChild(current);         //el nuevo nodo tiene como hijo a j
                    current->setFather(newNode);        //j tiene como padre al nuevo nodo
                }//ver caso en que no se solapa con ninguno?
            }
            new_nodes_prev.push_back(newNode);

            k++;
        }
        nodes_prev = new_nodes_prev;
        //iterar
        niveles++;
    }
    std::cout<<"Se termino de construir la estructura de Kirkpatrick con "<<niveles<<" niveles\n";
}

void Kirkpatrick::print() {
    std::cout<<"Impresion de la estructura de Kirkpatrick\n";
    this->root->print(0);
    std::cout<<"Fin de impresion\n";
}
