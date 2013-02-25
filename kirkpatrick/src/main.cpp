#include <GL/glut.h>
#include "Graph.h"
#include "utils.cpp"
#include <iostream>
#include <ctime>
#include <string>
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
    graph_to_draw->drawPoints();

    //Dibuja las lineas
    glLineWidth(1);
    glColor3f(0,0,1);
    graph_to_draw->drawLines();

    //Dibuja el triangulo presionado
    if (point_in_triangle) {
        glColor3f(1,1,0);
        point_in_triangle->draw();
    }
    //Dibuja el punto presionado
    if (point_pressed) {
        glColor3f(1,0,1);
        glPointSize(6); 
        glBegin(GL_POINTS);
            glVertex2f(point_pressed->x, point_pressed->y);
        glEnd();
    }
    //intercambia buffers 
    glutSwapBuffers();
}

//Callback de dibujado
void display_cb2() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Dibuja los puntos
    glColor3f(1,0,0);     
    glPointSize(5); 
    kirkpatrickStructure->G->drawPoints();

    //Dibuja las lineas
    glLineWidth(1);
    glColor3f(0,0,1);
    kirkpatrickStructure->G->drawLines();

    //Dibuja el punto presionado
    if (point_pressed) {
        glColor3f(1,0,1);
        glPointSize(6); 
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
        clock_t t_ini, t_end;
        double secs;
        t_ini = clock();

        if (kirkpatrickStructure->searchPoint(P, ret_val)) {
            //t_end = clock();   secs = (double (t_end - t_ini) );  std::cout<<"Tiempo "<<secs<<'\n';
            point_in_triangle = new TriangleStatic(ret_val);
            std::cout<<"Punto dentro de "; point_in_triangle->print(true);
        }
        else {
            std::cout<<"Punto fuera de la triangulacion\n";
        }
        glutPostRedisplay();
    } // fin botón izquierdo
    
}

void Mouse_cb2(int button, int state, int x, int y){
    if (button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN){ // boton derecho, borra un punto
        kirkpatrickStructure->step();
        kirkpatrickStructure->print();
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
    
    //Ventana donde se muestra el grafo estatico
    glutInitWindowPosition (0,200);
    glutCreateWindow ("Kirkpatrick: Grafo para busqueda");
    glutDisplayFunc (display_cb);
    glutReshapeFunc (reshape_cb);
    glClearColor(0.1f,0.1f,0.1f,1.f);
    glutMouseFunc(Mouse_cb);
    //glutMotionFunc(Motion_cb);
    
    
    glutInitWindowPosition (700,200);
    glutCreateWindow ("Kirkpatrick: Grafo para iterar");
    glutDisplayFunc (display_cb2);
    glutReshapeFunc (reshape_cb);
    glutMouseFunc(Mouse_cb2);
    //glutMotionFunc(Motion_cb);
    
    
    glClearColor(0.f,0.f,0.f,1.f);
}


int main(int argc, char **argv) {
    std::string test_case;
    if (argc > 1) {
        test_case = utils::ctos(argv[1]);
        std::cout<<"Leyendo caso "<<test_case;
    }
    else 
        test_case = "1";
    std::string str1 = "points" + test_case + ".txt";
    std::string str2 = "neighbors" + test_case + ".txt";
    std::string str3 = "triangles" + test_case + ".txt";
    graph_to_draw = new Graph(str1, str2, str3);
    graph = new Graph(str1, str2, str3);
    kirkpatrickStructure = new Kirkpatrick(graph, MAX_DEGREE);
    kirkpatrickStructure->build(0);
    std::cout<<"\n\n\nEstructura de Kirkpatrick:\n";
    kirkpatrickStructure->print();
    
    glutInit (&argc, argv);
    initialize();
    glutMainLoop();
    return 0;
}
