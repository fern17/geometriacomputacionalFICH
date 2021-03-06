#include <GL/glut.h>
#include <iostream>
#include "Utils.h"
#include "KDTree.h"
#include <unistd.h>
//Variable global que almacena el kdtree
KDTree * kdtree;

void printTree() {
    std::cerr<<"Arbol:\n";
    kdtree->print();
    std::cerr<<"\n";
}

void printMinimum() {
    Point minX = kdtree->findMin(true);
    Point minY = kdtree->findMin(false);
    std::cout<<"\nMinimo X = "; 
    minX.print();
    std::cout<<"\nMinimo Y = "; 
    minY.print();
    std::cout<<"\n";
}


//Declaracion de los callbacks
void Mouse_cb(int button, int state, int x, int y);
void PassiveMotion_cb(int xm, int ym);

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
    glBegin(GL_POINTS);
        kdtree->printPoints(); 
    glEnd();

    //Dibuja las lineas
    glLineWidth(1);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        kdtree->printLines();
    glEnd();
    
    printTree();
   
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
    //glutPassiveMotionFunc(PassiveMotion_cb);
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
    //std::cerr << x << "," << y << "," << button << std::endl;
    if (button==GLUT_MIDDLE_BUTTON and state==GLUT_DOWN){ // boton del medio
        Node *deleted = kdtree->remove();
        if (deleted) {
            std::cerr<<"Nodo borrado: "; 
            deleted->point.print();
            std::cerr<<'\n';
            printTree();
            glutPostRedisplay();
        }
    }
    
    if (button==GLUT_LEFT_BUTTON and state==GLUT_DOWN){ // boton izquierdo
        y = 480-y;
        kdtree->insert( Point(x,y) );

        glutPostRedisplay();
    } // fin botón izquierdo
    if (button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN){ // boton derecho
        PassiveMotion_cb(x,y);
    }
}

void PassiveMotion_cb(int xm, int ym){
    ym = 480-ym;
    //Codigo copiado del display_cb
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
    //fin codigo display_cb
    
    //Dibuja el cuadrado al que pertenece el punto que esta apuntado por el mouse
    
    Point P(xm, ym);
    
    Node *boss = kdtree->search(P);
    if (boss->point.isNULL()) return;
    
    
    glColor3f(0,1,1);
    glLineWidth(2);
    glBegin(GL_LINES);
        if(boss->limits[Node::LEFT]) {
            glVertex2f(boss->limits[Node::LEFT]->point.x, 0); 
            glVertex2f(boss->limits[Node::LEFT]->point.x, 480);
        }
        
        if(boss->limits[Node::RIGHT]) {
            glVertex2f(boss->limits[Node::RIGHT]->point.x, 0); 
            glVertex2f(boss->limits[Node::RIGHT]->point.x, 480);
        } 
        
        if(boss->limits[Node::UP]) {
            glVertex2f(0,   boss->limits[Node::UP]->point.y); 
            glVertex2f(640, boss->limits[Node::UP]->point.y);
        }
        
        if(boss->limits[Node::DOWN]) {
            glVertex2f(0,   boss->limits[Node::DOWN]->point.y); 
            glVertex2f(640, boss->limits[Node::DOWN]->point.y);
        }
    glEnd();
   
    glutSwapBuffers();
}
