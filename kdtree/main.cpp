#include <GL/glut.h>
#include <iostream>
#include "Utils.h"
#include "KDTree.h"

KDTree * kdtree;
void Mouse_cb(int button, int state, int x, int y);

void reshape_cb (int w, int h) {
    if (w==0||h==0) return;
    glViewport(0,0,w,h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0,w,0,h);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);     
    glPointSize(5); 
    glBegin(GL_POINTS);
        kdtree->printPoints(); 
    glEnd();

    glLineWidth(1);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        kdtree->printLines();
    glEnd();
    glutSwapBuffers();
}

void initialize() {
    glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize (640,480);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Ventana OpenGL");
    glutDisplayFunc (display_cb);
    glutReshapeFunc (reshape_cb);
    glutMouseFunc(Mouse_cb);
    glClearColor(0.f,0.f,0.f,1.f);
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    initialize();
    std::vector<Point> points = Utils::readFile("puntos.txt");
    kdtree = new KDTree(points);

    glutMainLoop();
    return 0;
}


void Mouse_cb(int button, int state, int x, int y){
    std::cerr << x << "," << y << "," << button << std::endl;
    if (button==GLUT_LEFT_BUTTON and state==GLUT_DOWN){ // boton izquierdo
        y = 480-y;
        kdtree->insert( Point(x,y) );

        glutPostRedisplay();
    } // fin botón izquierdo
}
