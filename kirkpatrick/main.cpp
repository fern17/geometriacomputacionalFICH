#include <GL/glut.h>
#include "Graph.h"
#include "utils.cpp"
#include <iostream>

Graph *graph;

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
    graph->drawPoints();

    //Dibuja las lineas
    glLineWidth(1);
    glColor3f(0,0,1);
    graph->drawLines();
    
    glutSwapBuffers();
}

void Mouse_cb(int button, int state, int x, int y){
    if (button==GLUT_MIDDLE_BUTTON and state==GLUT_DOWN){ // boton del medio
    }
    
    if (button==GLUT_LEFT_BUTTON and state==GLUT_DOWN){ // boton izquierdo
        y = 480-y;
        Point P(x,y);
        graph->deleteNearest(P);
        //kirkpatrick.locatePoint(x,y);
        glutPostRedisplay();
    } // fin botón izquierdo
    
    if (button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN){ // boton derecho
    }
}

void initialize() {
    glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize (640,480);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Kirkpatrick Structure");
    glutDisplayFunc (display_cb);
    glutReshapeFunc (reshape_cb);
    glutMouseFunc(Mouse_cb);
    glClearColor(0.f,0.f,0.f,1.f);
}


int main(int argc, char **argv) {
    graph = new Graph("points.txt", "neighbors.txt", "triangles.txt");
    glutInit (&argc, argv);
    initialize();
    glutMainLoop();
    return 0;
}