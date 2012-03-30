#include <list>
#include <stack>
#include "Point2D.h"
#include <iostream>
#include <GL/glut.h>

std::stack<Point2D> S;
std::list<Point2D> Q;

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
    glColor3f(1,1,0); glLineWidth(3);
    
    glBegin(GL_POINTS);
        std::list<Point2D>::iterator p = Q.begin();
        while(p != Q.end()){
            Point2D p = *p;
            glVertex2f(p.x, p.y);
            p++
        }
    glEnd();
    
    std::list<Point2D> listaDePuntos(S);
    glBegin(GL_LINE_STRIP);
        std::list<Point2D>::iterator p = listaDePuntos.begin();
        while(p != listadePuntos.end()){
            Point2D p = *p;
            glVertex2f(p.x, p.y);
            p++
        }
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
    glClearColor(1.f,1.f,1.f,1.f);
}


void printList(std::list<Point2D> &Q){
  std::list<Point2D>::iterator it = Q.begin();
  std::cout<<"Lista:\n";
  while(it != Q.end()){
    it->print();
    it++;
  }
}
void leer(std::list<Point2D> &Q, unsigned int n){
  for(unsigned int i = 0; i < n; i++){
    Point2D p;
    std::cin>>p.x;
    std::cin>>p.y;
    Q.push_back(p);
  }
  //printList(Q);
}


void printStack(std::stack<Point2D> &S){
  std::stack<Point2D> ss(S);
  std::cout<<"Pila:\n";
  while(!ss.empty()){
    ss.top().print();
    ss.pop();
  }
}

extern void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S);

void play(){
    int n;
    std::cin>>n; 
    leer(Q, n);
    grahamScan(Q,S);
}

int main(){
//  std::list<Point2D> points;
  unsigned int n;
  glutInit (&argc, argv);
  initialize();
  play();
  glutMainLoop();
  
  
  return 0;
}
