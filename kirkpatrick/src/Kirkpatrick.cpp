#include "Kirkpatrick.h"
#include "utils.cpp"
#include <iostream>

//Constructor que toma el grafo y un maximo de grado
Kirkpatrick::Kirkpatrick(Graph * _G, unsigned int _max_degree) {
    this->root = NULL;      //No hay nada en la raiz
    this->G = _G;
    this->max_degree = _max_degree;
}

//Construye la estructura de Kirkpatrick.
//Realiza tantos pasos en la construccion como se indica como parametro
//Si este parametro es -1, realiza la construccion hasta que se quede sin triangulos (estructura completa)
void Kirkpatrick::build(int max_steps) {
    unsigned int graphsize = this->G->size();   //cantidad de puntos

    if (graphsize < 3) {
        std::cout<<"No se pudo construir el DAG porque no se tienen suficientes puntos\n";
        return;
    }
    
    //Variable utilizada para actualizar los hijos al crear un nuevo nivel
    this->nodes_prev.clear();           //guarda los nodos que se agregaron en el paso anterior
    this->nodes_prev.reserve(graphsize);
    
    std::cout<<"Construyendo estructura de Kirkpatrick\n";
    //Primero se crea el nodo raiz con el triangulo envolvente
    Node * root_node = new Node(this->G->getBoundingTriangle());
    this->root = root_node;
    
    //Ahora se agregan como hijos de la raiz, nodos formados por cada uno de los triangulos
    std::list<Triangle>::iterator i = this->G->triangles.begin();
    while (i != this->G->triangles.end()) {
        //Se crea un triangulo estatico a partir de uno dinamico
        Node *to_add = new Node(TriangleStatic::buildFromTriangle(*i));
        //Y se agrega como hijo
        this->root->addChild(to_add);
        this->nodes_prev.push_back(to_add);
        i++;
    }
    
    //A continuacion, se debe iterar, borrar puntos y cambiar los padres de cada triangulo
    unsigned int niveles = 1; //contador de niveles en el arbol
    while (max_steps == -1 or niveles <= max_steps) { //va a terminar con un break o cuando se alcancen los niveles
        std::cout<<"Procesando nivel "<<niveles<<"\n";
        bool next = this->step();
        if (not next)
            break;
        else
            niveles++;
    }
    std::cout<<"Se termino de construir la estructura de Kirkpatrick con "<<niveles<<" niveles\n";
}

//Realiza un paso de la construccion de la estructura. Llama a Graph::kirkpatrickDeletion
bool Kirkpatrick::step() {
    //probar si se pueden borrar puntos
    if (this->G->size() <= 3) {
        std::cout<<"Ya no se pueden borrar más puntos, terminando la construccion de la estructura de Kirkpatrick\n";
        return false;   //Este false es capturado por build() y termina la construccion
    }
    
    //borrar puntos
    unsigned int cantidad_borrados = this->G->kirkpatrickDeletion(this->max_degree); //borra puntos y retorna la cantidad borrados
    std::cout<<"Se borraron "<<cantidad_borrados<<" puntos del grafo.\n"; 
    
    if (cantidad_borrados == 0) 
        return false; //ya no se pueden borrar más, salgo del while de build

    std::vector<Node *> new_nodes_prev; //vector que almacena los nodos del nivel Ti-1

    std::list<Triangle>::iterator k = this->G->triangles.begin(); //k itera en los nuevos triangulos del grafo
    
    //Para cada triangulo en graph, ver con cuales se solapa de todos los triangulos del nivel siguiente, y marcarlo como padre
    while (k != this->G->triangles.end()) {
        //para el triangulo k
        Node *newNode = new Node(TriangleStatic::buildFromTriangle(*k)); //se crea un nuevo nodo sin padre
        
        //se recorren todos los nodos del nivel siguiente
        for (unsigned int j = 0; j < this->nodes_prev.size(); j++) {
            Node *current = this->nodes_prev[j];
            
            //si se superpone k con j, k es padre de j
            if (utils::triangleOverlap( *newNode->triangle, 
                                        *current->triangle)) {
                this->root->deleteChild(current);       //current ya no es hijo de root
                newNode->addChild(current);             //el nuevo nodo tiene como hijo a j
            }
        }
        this->root->addChild(newNode);                  //newNode es hijo de root
        new_nodes_prev.push_back(newNode);              //Lo agrego a new_nodes_prev para el paso siguiente

        k++;
    }
    this->nodes_prev = new_nodes_prev;                  //actualizo nodes_prev para ser usado en el paso siguiente
    return true;
}

//Imprime la estructura por la salida estandar
void Kirkpatrick::print() {
    std::cout<<"Impresion de la estructura de Kirkpatrick\n";
    this->root->print(0);
    std::cout<<"Fin de impresion\n";
}

//Busca un punto dentro de la estructura en tiempo logaritmico
bool Kirkpatrick::searchPoint(Point P, TriangleStatic &ret_val) {
    return this->root->search(P, ret_val, 0);
}
