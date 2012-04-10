#include <list>
#include <stack>
#include "Point2D.h"
#include <iostream>
#include <GL/glut.h>
#include <algorithm>

std::stack<Point2D> S;
std::list<Point2D> Q;
std::list<Point2D> QQ;
std::pair<Point2D, Point2D> fPair;
float maxDist;

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
   
    std::stack<Point2D> temp(S);

    std::list<Point2D> listaDePuntos;
    while(temp.size() != 0){
        listaDePuntos.push_front(temp.top());
        temp.pop();
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
    glColor3f(0.5,0.5,1);
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
        glVertex2f(fPair.first.x, fPair.first.y);
        glVertex2f(fPair.second.x, fPair.second.y);
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


void printStack(std::stack<Point2D> &S){
  std::stack<Point2D> ss(S);
  std::cout<<"Pila:\n";
  while(!ss.empty()){
    ss.top().print();
    ss.pop();
  }
}

extern void grahamScan(std::list<Point2D> & Q, std::stack<Point2D> & S);
extern void farthestPair(std::list<Point2D> & Q, std::pair<Point2D, Point2D> & FP, float & maxDistance);
extern void farthestn2(std::list<Point2D> &Q, std::pair<Point2D, Point2D> &FP, float &maxDistance);
extern float chPerimeter(std::list<Point2D> & Q);

void play(){
    int n;
    std::cin>>n; 
    leer(Q, n);
    QQ = Q;
    grahamScan(Q,S);
    std::stack<Point2D> ss(S);
    std::list<Point2D> listaS;
    while(!ss.empty()){
        listaS.push_back(ss.top());
        ss.pop();
    }
    
    std::cout<<"Rotating Calipers (N):\n";
    farthestPair(listaS, fPair, maxDist);
    std::cout<<"Maximum Distance: "<<maxDist<<"\n";
    fPair.first.print();
    fPair.second.print();
    
    //std::cout<<"N2:\n";
    //farthestn2(listaS, fPair, maxDist);
    //std::cout<<"Maximum Distance: "<<maxDist<<"\n";
    //fPair.first.print();
    //fPair.second.print();

    float perimeter = chPerimeter(listaS);
    std::cout<<"Perimeter: "<<perimeter<<std::endl;
}

int main(int argc, char **argv){
  unsigned int n;
  glutInit (&argc, argv);
  initialize();
  play();
  glutMainLoop();
  
  return 0;
}
