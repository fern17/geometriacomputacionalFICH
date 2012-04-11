#include <list>
#include <deque>
#include "Point2D.h"
#include <iostream>
#include <GL/glut.h>
#include <algorithm>

std::deque<Point2D> D;
std::list<Point2D> Q;
std::list<Point2D> QQ;

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
    glColor3f(1,0,0); glLineWidth(3);
    glPointSize(7); 
    glBegin(GL_POINTS);
        std::list<Point2D>::iterator p = QQ.begin();
        while(p != QQ.end()){
            Point2D point = *p;
            glVertex2f(point.x, point.y);
            p++;
        }
    glEnd();
   
    std::list<Point2D> listaDePuntos;
    for(int k = 0; k < D.size(); k++){
        listaDePuntos.push_back(D.at(k));
    }
    
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
        std::list<Point2D>::iterator q = listaDePuntos.begin();
        while(q != listaDePuntos.end()){
            Point2D point = *q;
            glVertex2f(point.x, point.y);
            q++;
        }
    glEnd();
    glutSwapBuffers();
}

void initialize() {
    glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize (640,480);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Convex Hull");
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

void printDeque(std::deque<Point2D> &D){
    std::cout<<"Deque:\n";
    for(unsigned int i = 0; i < D.size(); i++){
        D.at(i).print();
    }
    std::cout<<"\n";
}

extern void melkman(std::list<Point2D> & Q, std::deque<Point2D> & D);

void play(){
    int n;
    std::cin>>n; 
    leer(Q, n);
    QQ = Q;
    melkman(Q,D);
    std::list<Point2D> listaS;
    for(int k = 0; k < D.size(); k++){
        listaS.push_back(D.at(k));
    }
}

int main(int argc, char **argv){
  unsigned int n;
  glutInit (&argc, argv);
  initialize();
  play();
  glutMainLoop();
  
  return 0;
}
