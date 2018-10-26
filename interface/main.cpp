#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include <fstream>

#define KEY_ESC 27

using namespace std;

const float extern_d_y = 900; //Marco vertical
const float extern_d_x = 900; //Marco horizontal

vector<float> points_y = vector<float>(0, 0.0); //Ver
vector<float> points_x = vector<float>(0, 0.0); //horizontal

int num_fila = 16; //Ver
int num_columnas = (int)(num_fila * (0.725)); //horizontal



void init_GL(void);
void glPaint(void);
void OnMouseClick(int, int, int, int);
void OnMouseMotion(int, int);
void idle();
GLvoid window_redraw(GLsizei, GLsizei);
GLvoid window_key(unsigned char, int, int);

void translate_points(float&, float&);//Adapt incoming data to the new format needed in opengl map
void get_point(float&, float&);

void points_distribution();
void DrawCircle(float, float, int);
void draw_points();
void draw_lines();
void draw_main_points();



int main(int argc, char** argv){
  points_distribution();

  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(extern_d_x, extern_d_y); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Interfaz"); //titulo de la ventana

	init_GL();
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);

	glutKeyboardFunc(&window_key);
  glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
  glutIdleFunc(&idle);
  glutMainLoop(); //bucle de rendering
  return 0;
}

void points_distribution(){
  float salt_vertical = extern_d_y/(num_fila - 1) ;
  float salt_horizontal = extern_d_x/(num_columnas - 1 );

  cout<<num_columnas<<" "<<num_fila<<endl;
  cout<<salt_horizontal<<"   "<<salt_vertical<<endl;

  float mod_y;
  float mod_x;

  for(int i = 0, mod_y = 0.0; i < num_fila; i++, mod_y+=salt_vertical){ //Filas
    for(int j = 0, mod_x = 0.0; j < num_columnas; j++, mod_x+=salt_horizontal){  //Columnas
        points_y.push_back(mod_y);
        points_x.push_back(mod_x);
    }
  }
  /*
  for(unsigned int i = 0; i < points_y.size(); i++){
    cout<<points_x[i]<<" "<<points_y[i]<<endl;
  }
  cout<<endl;*/

}

void draw_points(){
  glPointSize(3);
  glColor3f(9.0f, 0.0f, 0.0f);
  glBegin(GL_POINTS);

  for(unsigned int i = 0; i < grafo_list.adyacentes.size(); i++){
    if(grafo_list.adyacentes[i].visible){
      glVertex2f(grafo_list.adyacentes[i].y, grafo_list.adyacentes[i].x);
    }
    glVertex2f(points_distribution_y[i], points_distribution_x[i]);
  }
  //for(unsigned int i = 0; i < points_distribution_x.size(); i++){
    //DrawCircle(points_distribution_x[i], points_distribution_y[i], 1);
    //glVertex2f(points_distribution_y[i], points_distribution_x[i]);
  //}
  glEnd();
}

void draw_lines(){
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  for(unsigned int i = 0; i < points_y.size(); i++){
      glVertex2f(points_y[i], 0);
      glVertex2f(points_y[i], extern_d_x);

      glVertex2f(0, points_x[i]);
      glVertex2f(extern_d_y, points_x[i]);
  }
  glEnd();
}

void DrawCircle(float cx, float cy, int r){
}

//Unusable
void translate_points(float& _x, float& _y){
  _x = (_x * extern_d_x) / glutGet(GLUT_WINDOW_HEIGHT);
  _y = (_y * extern_d_y) / glutGet(GLUT_WINDOW_WIDTH);
}



void draw_main_points(){
  glPointSize(5);
  glColor3f(10.0f, 10.0f, 10.0f);
  glBegin(GL_POINTS);
      //glVertex2f(grafo_list.adyacentes[i].y, grafo_list.adyacentes[i].x);
      //glVertex2f(grafo_list.adyacentes[grafo_list.initial_point].y, grafo_list.adyacentes[grafo_list.initial_point].x);
      //glVertex2f(grafo_list.adyacentes[grafo_list.final_point].y, grafo_list.adyacentes[grafo_list.final_point].x);
  glEnd();
}

void get_point(float& a, float& b){
  a = a / ( (float)glutGet(GLUT_WINDOW_WIDTH)/extern_d_x);
	//b = ( (float)glutGet(GLUT_WINDOW_HEIGHT) - b ) / ( (float)glutGet(GLUT_WINDOW_HEIGHT) / extern_d_y);
  b = b / ((float)glutGet(GLUT_WINDOW_HEIGHT) / extern_d_y);
}

void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);//Setting up configuration of  inner windows
  //glOrtho( 0.0f, windowWidth, windowHeight,  0.0f, 0.0f, 1.0f);//Setting up configuration of  inner windows
  glOrtho( 0.0f, extern_d_y, extern_d_x,  0.0f, 0.0f, 1.0f);//Setting up configuration of  inner windows
  //glOrtho( 0.0f, 1300.0f, 700.0f,  0.0f, 0.0f, 1.0f);//Setting up configuration of  inner windows
  ///////////////////////Funciones a trabajar//////////////////////////////////////
  //draw_points();
  draw_lines();
  glutSwapBuffers();
}


void OnMouseClick(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
	float x_2 = (float)x;
	float y_2 = (float)y;
  get_point(x_2, y_2);
  cout<<x_2<<";"<<y_2<<endl;
  //cout<<grafo_list.initial_point<<" - "<<grafo_list.final_point<<endl;
  }

  /*if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
  //  cout<<"Click para eliminar"<<endl;
    float x_2 = (float)x;
    float y_2 = (float)y;
    get_point(x_2, y_2);

  }*/
}

void OnMouseMotion(int x, int y){
}

void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
  case 'b':
    //bf_controller = !bf_controller;
    //if(bf_controller){
      //grafo_list.alg_profundidad();
  //  }
    break;
  case 'c':
    //climbing_controller = !climbing_controller;
    //if(climbing_controller){
      //grafo_list.alg_climbing();
    //}
    break;
	default:
		break;
	}
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  glOrtho( 0.0f, extern_d_y, extern_d_x,  0.0f, 0.0f, 1.0f);
  //glOrtho( 0.0f, 1300.0f, 700.0f,  0.0f, 0.0f, 1.0f);
  //glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);
	//glOrtho(mar_iz_down.x,  mar_der_up.x, mar_iz_down.y, mar_der_up.y, -1.0f, 1.0f);//Setting up configuration of  inner windows
}
