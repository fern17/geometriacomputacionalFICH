#include "Kirkpatrick.h"
#include <iostream>
Kirkpatrick::Kirkpatrick() {
    this->root = NULL;
}


void Kirkpatrick::build(Graph *G, unsigned int max_degree) {
    if (G->size() < 3) {
        std::cout<<"No se pudo construir el DAG porque no se tienen suficientes puntos\n";
        return;
    }
    //Primero se crea el nodo raiz con el triangulo envolvente
    TriangleStatic rootie = G->getBoundingTriangle();
    Node * root_node = new Node(rootie, NULL);
    this->root = root_node;
    std::vector<Node *> nodes_prev; //en este vector se almacenaran los nodos que se agregan en cada nivel del arbol, para iterar en el nivel siguiente
    //Ahora se agregan como hijos de la raiz, nodos formados por cada uno de los triangulos
    for (unsigned int i = 0; i < G->triangles.size(); i++) {
        //Se crea un triangulo estatico a partir de uno dinamico
        TriangleStatic tri = TriangleStatic::buildFromTriangle(G->triangles[i]);
        Node *to_add = new Node(tri, this->root);
        //Y se agrega como hijo
        this->root.addChild(to_add);
        nodes_prev.push_back(to_add);
    }

    //A continuacion, se debe iterar, borrar puntos y cambiar los padres de cada triangulo
    
    while (true) {
        //probar si se pueden borrar puntos
        if (G->size() <= 3) {
            std::cout<<"Ya no se pueden borrar más puntos, terminando la construccion de la estructura de Kirkpatrick\n";
            return;
        }
        //borrar puntos
        G->kirkpatrickDeletion(max_degree);
        std::vector<Node *> new_nodes_prev;
        //Para cada triangulo en graph, ver con cuales se solapa de todos los triangulos del nivel anterior, y marcarlo como padredd
        for (unsigned int i = 0; i < G->triangles.size(); i++) {
            Node *newNode = new Node(G->triangles[i], NULL); //se crea un nuevo nodo sin padre
            for (unsigned int j = 0; j < nodes_prev.size(); j++) {
                Node *current = nodes_prev[j];
                //si se superpone i con j, i es padre de j
                if (utils::triangleOverlap( TriangleStatic::buildFromTriangle(G->triangles[i]), 
                                            current->triangle)) {
                    Node *old_father = current->father; //antiguo padre de j
                    old_father->deleteChild(current);   //j ya no es hijo de su antiguo padre
                    old_father->addChild(newNode);       //le agrego al padre el hijo nuevo
                    newNode->setFather(newNode);        //se le actualiza el padre al nodo actual
                    newNode->addChild(current);         //el nuevo nodo tiene como hijo a j
                    current->setFather(newNode);        //j tiene como padre al nuevo nodo
                }//ver caso en que no se solapa con ninguno?
            }
            new_nodes_prev.push_back(newNode);
        }
        nodes_prev = new_nodes_prev;
        //iterar
    }
}
