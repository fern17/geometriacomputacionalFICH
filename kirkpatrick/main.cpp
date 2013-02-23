#include <GL/glut.h>
#include "Graph.h"
#include "utils.cpp"
#include <iostream>
#include "Kirkpatrick.h"
#include "TriangleStatic.h"
static const unsigned int MAX_DEGREE = 8;
char TriangleStatic::TAG = '@';

Graph *graph;           //grafo que usa kirkpatrick
Graph *graph_to_draw;   //grafo para dibujar
Kirkpatrick *kirkpatrickStructure;
TriangleStatic *point_in_triangle;
Point * point_pressed;

//Cosas de OPENGL
//Callback de Resize
void reshape_cb (int w, int h) {
    if (w == 0 or h == 0) return;
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

//Callback de dibujado
void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Dibuja los puntos
    glColor3f(1,0,0);     
    glPointSize(5); 
    //graph_to_draw->drawPoints();
    kirkpatrickStructure->G->drawPoints();

    //Dibuja las lineas
    glLineWidth(1);
    glColor3f(0,0,1);
    //graph_to_draw->drawLines();
    kirkpatrickStructure->G->drawLines();

    //Dibuja el triangulo presionado
    if (point_in_triangle) {
        glColor3f(0,1,0);
        point_in_triangle->draw();
    }
    //Dibuja el punto presionado
    if (point_pressed) {
        glColor3f(1,0,0);
        glPointSize(8); 
        glBegin(GL_POINTS);
            glVertex2f(point_pressed->x, point_pressed->y);
        glEnd();
    }
    //intercambia buffers 
    glutSwapBuffers();
}

void Mouse_cb(int button, int state, int x, int y){
    if (button==GLUT_MIDDLE_BUTTON and state==GLUT_DOWN){ // boton del medio, realiza una iteracion de kirkpatrick
        kirkpatrickStructure->step();
        kirkpatrickStructure->print();
        glutPostRedisplay();
    }
    
    if (button==GLUT_LEFT_BUTTON and state==GLUT_DOWN){ // boton izquierdo, ubica un punto
        y = 480-y;
        Point P(x,y);
        delete point_pressed;
        point_pressed = new Point(P);
        delete point_in_triangle;
        
        TriangleStatic ret_val;
        if (kirkpatrickStructure->searchPoint(P, ret_val)) {
            point_in_triangle = new TriangleStatic(ret_val);
            std::cout<<"Punto dentro de "; point_in_triangle->print(true);
        }
        else {
            std::cout<<"Punto fuera de la triangulacion\n";
        }
        //point_in_triangle = new TriangleStatic(kirkpatrickStructure->searchPoint(P));
        //std::cout<<"Punto dentro de "; point_in_triangle->print(true);
        glutPostRedisplay();
    } // fin botón izquierdo
    
    if (button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN){ // boton derecho, borra un punto
        Point P(x,y);
        kirkpatrickStructure->G->deleteNearest(P);
        //kirkpatrickStructure->G->printStructure();
        glutPostRedisplay();
    }
}

void Motion_cb(int x, int y) {
    y = 480-y;
    Point P(x,y);
    delete point_pressed;
    point_pressed = new Point(P);
    delete point_in_triangle;

    TriangleStatic ret_val;
    if (kirkpatrickStructure->searchPoint(P, ret_val)) {
        point_in_triangle = new TriangleStatic(ret_val);
        std::cout<<"Punto dentro de "; point_in_triangle->print(true);
    }
    else {
        std::cout<<"Punto fuera de la triangulacion\n";
    }
//    glutPostRedisplay();
   
}

void initialize() {
    glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize (640,480);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Kirkpatrick Structure");
    glutDisplayFunc (display_cb);
    glutReshapeFunc (reshape_cb);
    glutMouseFunc(Mouse_cb);
    //glutMotionFunc(Motion_cb);
    glClearColor(0.f,0.f,0.f,1.f);
}


int main(int argc, char **argv) {
    graph_to_draw = new Graph("points3.txt", "neighbors3.txt", "triangles3.txt");
    //graph_to_draw = new Graph("points.txt", "neighbors.txt", "triangles.txt");
    //graph = new Graph("points.txt", "neighbors.txt", "triangles.txt");
    graph = new Graph("points3.txt", "neighbors3.txt", "triangles3.txt");
    kirkpatrickStructure = new Kirkpatrick(graph, MAX_DEGREE);
    kirkpatrickStructure->build(0);
    std::cout<<"\n\n\nEstructura de Kirkpatrick:\n";
    kirkpatrickStructure->print();
    
    glutInit (&argc, argv);
    initialize();
    glutMainLoop();
    return 0;
}
