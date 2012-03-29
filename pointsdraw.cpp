#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
typedef struct Punto{
    float x;
    float y;
    float z;
}Punto;

std::vector<Punto> puntos;

//------------------------------------------------------------
// variables globales y defaults

int
  w=640, h=480, // tamaño de la ventana
  boton=-1, // boton del mouse clickeado
  xclick,yclick, // x e y cuando clickeo un boton
  plano; // 0=x 1=y 2=z

float
  escala = 100, escala0, // escala de los objetos window/modelo pixeles/unidad
  eye[] = {0,0,5}, target[] = {0,0,0}, up[] = {0,1,0}, // camara, mirando hacia y vertical
  znear = 2.f, zfar = 8.f, //clipping planes cercano y alejado de la camara (en 5 => veo de 3 a -3)
  amy, amy0, // angulo del modelo alrededor del eje y
  ac0, rc0; // angulo resp x y distancia al target de la camara al clickear

bool // variables de estado de este programa
  perspectiva=true, // perspectiva u ortogonal
  rota=false,       // gira continuamente los objetos respecto de y
  dibuja=true,      // false si esta minimizado
  wire=false,       // dibuja lineas o no
  relleno=true,     // dibuja relleno o no
  smooth=true,      // normales por nodo o por plano
  cl_info=true,     // informa por la linea de comandos
  antialias=false,  // antialiasing
  blend=false;      // transparencias

short modifiers = 0;  // ctrl, alt, shift (de GLUT)
static const double PI = 4*atan(1.0), R2G = 180/PI;

inline short get_modifiers() {return modifiers=(short)glutGetModifiers();}

// Regenera la matriz de proyeccion
// cuando cambia algun parametro de la vista

void regen() {
//  if (cl_info) cout << "regen" << endl;
  if (!dibuja) return;

  // matriz de proyeccion
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // semiancho y semialto de la ventana a escala en el target
  double w0 = (double) w/2/escala;
  double h0 = (double) h/2/escala;
  // frustum, perspective y ortho son respecto al eye con los z positivos
  if (perspectiva){ // perspectiva
    double
      delta[3] = {(target[0]-eye[0]),
                (target[1]-eye[1]),
                (target[2]-eye[2])},
      dist = sqrt(delta[0]*delta[0]+
                delta[1]*delta[1]+
                delta[2]*delta[2]);
      w0 *= znear/dist,
      h0 *= znear/dist; //w0 y h0 en el near
    glFrustum(-w0, w0, -h0, h0, znear, zfar);
  }
  else { // proyeccion ortogonal
    glOrtho(-w0, w0, -h0, h0, znear, zfar);
  }

  glMatrixMode(GL_MODELVIEW); glLoadIdentity(); // matriz del modelo

  gluLookAt(   eye[0],   eye[1],   eye[2],
              target[0],target[1],target[2],
                  up[0],    up[1],    up[2]);// ubica la camara
  // rota los objetos alrededor de y
  glRotatef(amy,0,1,0);

  glutPostRedisplay(); // avisa que hay que redibujar
}




void reshape_cb (int w, int h) {
    if (w==0||h==0) return;
    glViewport(0,0,w,h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(0,w,0,h);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    regen();
}

void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,0); glLineWidth(3);
    glPointSize(5);
    glBegin(GL_POINTS);
      for(unsigned int i = 0; i < puntos.size(); i++){
        Punto p = puntos[i];
        glVertex3f(p.x,p.y,p.z);
      }
    glEnd();
    glutSwapBuffers();
}

//------------------------------------------------------------
// Movimientos del mouse
void Motion_cb(int xm, int ym){ // drag
  if (boton == GLUT_LEFT_BUTTON){
    if (modifiers == GLUT_ACTIVE_SHIFT){ // cambio de escala
      escala = escala0 * exp((yclick-ym)/100.0);
      regen();
    }
    else { // manipulacion
      double yc = eye[1] - target[1];
      double zc = eye[2] - target[2];
      double ac = ac0 + (ym-yclick)*720.0 / h / R2G;
      
      yc = rc0*sin(ac);
      zc = rc0*cos(ac);
      
      up[1] = zc; 
      up[2] = -yc;  // perpendicular
      
      eye[1] = target[1]+yc;
      eye[2] = target[2]+zc;
      
      amy = amy0 + (xm-xclick)*180.0/w;
      regen();
    }
  }
}
// Clicks del mouse
// GLUT LEFT BUTTON, GLUT MIDDLE BUTTON, or GLUT RIGHT BUTTON
// The state parameter is either GLUT UP or GLUT DOWN
// glutGetModifiers may be called to determine the state of modifier keys
void Mouse_cb(int button, int state, int x, int y){
  static bool old_rota=false;
  if (button == GLUT_LEFT_BUTTON){
    if (state == GLUT_DOWN) {
      xclick = x; 
      yclick = y;
      boton = button;
      old_rota = rota; 
      rota = false;
      get_modifiers();
      glutMotionFunc(Motion_cb); // callback para los drags
      if (modifiers==GLUT_ACTIVE_SHIFT){ // cambio de escala
        escala0 = escala;
      }
      else { // manipulacion
        double yc = eye[1]-target[1];
        double zc = eye[2]-target[2];
        rc0 = sqrt(yc*yc+zc*zc);
        ac0 = atan2(yc,zc);
        amy0 = amy;
      }
    }
    else if (state==GLUT_UP){
      rota = old_rota;
      boton = -1;
      glutMotionFunc(0); // anula el callback para los drags
    }
  }
}

void initialize() {
    glutInitDisplayMode(GLUT_DEPTH|GLUT_RGB|GLUT_DOUBLE|GLUT_ALPHA);
    glutInitWindowSize (w,h);
    glutInitWindowPosition (50,50);
    glutCreateWindow ("Ventana OpenGL");
    glutDisplayFunc (display_cb);
    glutMouseFunc(Mouse_cb); // botones picados
    glutReshapeFunc (reshape_cb);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); // habilita el z-buffer

}

void leerPuntos(){
    unsigned int n;
    float x;
    float y;
    std::cin>>n;

    for(unsigned int i = 0; i < n; i++){
        Punto p;
        std::cin>>p.x;
        std::cin>>p.y;
        puntos.push_back(p);
    }
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    leerPuntos();
    initialize();
    glutMainLoop();
    return 0;
}
