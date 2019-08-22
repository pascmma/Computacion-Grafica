#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#define KEY_ESC 27
#define PI 3.14159265359

//dibuja un simple gizmo
void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255,0,0);
	glVertex2d(0, 0);
	glVertex2d(1, 0);
	glColor3d(0, 255, 0);
	glVertex2d(0, 0);
	glVertex2d(0, 1);
	glEnd();
}
void cuadrado(float cent_x,float cent_y,float arista)
{
    glBegin(GL_LINE_LOOP);
    glColor3d(255,0,0);
    glVertex2f(cent_x-arista,cent_y-arista);
    glVertex2f(cent_x+arista,cent_y-arista);
    glVertex2f(cent_x+arista,cent_y+arista);
    glVertex2f(cent_x-arista,cent_y+arista);
    glEnd();
}
void circulo(float cent_x,float cent_y,float radio)
{
    glBegin(GL_LINE_LOOP);
    int numPoints =50;
    for(int i=0;i<numPoints;i++)
    {
        float theta = (2*PI*i)/numPoints;
        glVertex2f(cent_x+radio*cos(theta),cent_y+radio*sin(theta));
    }
    glEnd();
}
void CirculosD(float cent_x,float cent_y,float radio,float cantidad,float porcentaje)
{
    glBegin(GL_LINE_LOOP);
    glColor3d(255,0,0);

    for(int i=0;i<cantidad;i++)
    {
        circulo(cent_x,cent_y,radio);
        cent_x = cent_x - radio;
        radio = radio-(radio*porcentaje);
        cent_x = cent_x + radio;
    }
    glEnd();
}
void CirculosE(float cent_x,float cent_y,float radio,float cantidad,float porcentaje)
{
    glBegin(GL_LINE_LOOP);
    glColor3d(0,0,0);
    for(int i=0;i<cantidad;i++)
    {
        circulo(cent_x,cent_y,radio);
        cent_x = cent_x + radio;
        radio = radio-(radio*porcentaje);
        cent_x = cent_x + radio;
    }
    glEnd();
}
void CirculosA(float cent_x,float cent_y,float radio,float cantidad,float porcentaje,float angulo)
{
    glBegin(GL_LINE_LOOP);
    glColor3d(0,0,0);
    for(int i=0;i<cantidad;i++)
    {
        circulo(cent_x,cent_y,radio);
        cent_x = cent_x +radio*cos(angulo);
        cent_y = cent_y +radio*sin(angulo);
        radio = radio-(radio*porcentaje);
        cent_x = cent_x +radio*cos(angulo);
        cent_y = cent_y +radio*sin(angulo);

    }
    glEnd();
}


//
//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(255, 255, 255, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();


	//dibuja el gizmo
	//cuadrado(0,0,10);
	//circulo(0,0,5);
	CirculosA(0,0,10,3,0.2,45);


	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-50.0f,  50.0f,-50.0f, 50.0f, -1.0f, 1.0f);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
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
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}

