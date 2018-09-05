#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include <fstream>
#include "c_grafo.h"

#define KEY_ESC 27

#define PI 3.14159265f


int extern_n_x = 50;
int extern_n_y = 50;
float extern_d_y = 1000;
float extern_d_x = 1000;
c_grafo grafo(extern_n_x, extern_n_y, extern_d_x, extern_d_y);
vector<float> points_distribution_x(extern_n_x * extern_n_y, 0);
vector<float> points_distribution_y(extern_n_x * extern_n_y, 0);
void translate_points(float&, float&);//Adapt incoming data to the new format needed in opengl map

using namespace std;

void init_GL(void);
void glPaint(void);
void OnMouseClick(int, int, int, int);
void OnMouseMotion(int, int);
void idle();
GLvoid window_redraw(GLsizei, GLsizei);
GLvoid window_key(unsigned char, int, int);

void points_distribution();
void DrawCircle(float, float, int);
void draw_points();
void draw_lines();

int main(int argc, char** argv){
  grafo.set_configuration(1);
  points_distribution();

  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1300, 700); //tama�o de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Grafo Simulation"); //titulo de la ventana

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
  int point_pointer = 0;
  float x_jump = extern_d_x/(extern_n_x-1) - 0.3;
  float y_jump = extern_d_y/(extern_n_y-1) - 0.3;
  float x_pointer = 0.3;
  float y_pointer = 0.3;

  for(int j = 0; j < extern_n_x; j++){
    for(int k = 0; k < extern_n_y; k++){
        points_distribution_x[point_pointer] = x_pointer;
        points_distribution_y[point_pointer] = y_pointer;
        y_pointer += y_jump;
        point_pointer++;
    }
    y_pointer = 0.3;
    x_pointer += x_jump;
  }

  /*for(unsigned int i = 0; i < points_distribution_x.size(); i++){
    cout<<i<<" :"<< points_distribution_x[i]<<" - "<<points_distribution_y[i]<<endl;
  }*/

}

void draw_points(){
  glPointSize(5);
  glBegin(GL_POINTS);
  glColor3f(9.0f, 0.0f, 0.0f);

  for(unsigned int i = 0; i < points_distribution_x.size(); i++){
    //DrawCircle(points_distribution_x[i], points_distribution_y[i], 1);
    glVertex2f(points_distribution_y[i], points_distribution_x[i]);
  }
  glEnd();
}

void draw_lines(){
  glBegin(GL_LINES);
  for(unsigned int i = 0; i < grafo.adyacentes.size(); i++){
    for(unsigned int j = 0; j < grafo.adyacentes[i].size(); j++){
      if(grafo.adyacentes[i][j] != 0){
          glVertex2f(points_distribution_y[i], points_distribution_x[i]);
          glVertex2f(points_distribution_y[j], points_distribution_x[j]);
      }
    }
  }
  glEnd();
}

void DrawCircle(float cx, float cy, int r){
  /*glBegin(GL_QUADS);
    glVertex2f( cx, cy);
    glVertex2f( cx + r, cy);
    glVertex2f( cx + r,  cy + r);
    glVertex2f( cx,  cy + r);
  glEnd();*/
}

void translate_points(float& _x, float& _y){
  _x = (_x * extern_d_x) / glutGet(GLUT_WINDOW_HEIGHT);
  _y = (_y * extern_d_y) / glutGet(GLUT_WINDOW_WIDTH);
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
  draw_points();
  draw_lines();
  //DrawCircle(0, 0, 1);
  glutSwapBuffers();
}


void OnMouseClick(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
	float x_2 = (float)x;
	float y_2 = (float)y;
  cout<<x_2<<";"<<y_2<<endl;
  translate_points(x_2, y_2);
  cout<<x_2<<";"<<y_2<<endl;
	//c_point tempo(x_2, y_2);
	//data_point.push_back(tempo);
	//convertir x,y
	//insertar un nuevo punto en el quadtree
	//arbol.insert(x_2, y_2);
	}
}

void OnMouseMotion(int x, int y){
	//float x_2 = (float)x;
	//float y_2 = (float)y;
	//translate_points(x_2, y_2);
	//c_point tempo(x_2, y_2);
	//data_point.push_back(tempo);
	//Sleep(0.5);
	//arbol.insert(x_2, y_2);
}

void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
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
