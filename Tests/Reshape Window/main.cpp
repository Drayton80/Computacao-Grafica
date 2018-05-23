#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_INITIAL_WIDTH 1024
#define WINDOW_INITIAL_HEIGHT 768

void display(void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -2.0f);

	// Desenhando os eixos de coordenadas:
	glBegin(GL_LINES);
		// Eixo X:
		glColor3f (0.4f, 0.4f, 0.4f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f (1.0f, 0.0f, 0.0f);
		glVertex3f(3.0f, 0.0f, 0.0f);
		// Eixo Y:
		glColor3f (0.4f, 0.4f, 0.4f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 3.0f, 0.0f);
		// Eixo Z:
		glColor3f (0.4f, 0.4f, 0.4f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f (0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();


	//glTranslatef(0.0f, -2.0f, 0.0f);
	/*
	for(int i = -100; i <= 100; i += 1){
		glBegin(GL_LINES);
			// Linha Horizontal:
			glColor3f (0.4f, 0.4f, 0.4f);
			glVertex3f(-100.0f, i, 0.0f);
			glVertex3f( 100.0f, i, 0.0f);		
		glEnd();
	}
	*/

	glFlush();
}

void reshape(int width, int height){
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argumentsC, char **argumentsV){
	glutInit(&argumentsC, argumentsV);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1024, 768);

	// Aqui na inicialização da janela faz com que ela inicialize no centro da tela
	//   Onde glutGet(GLUT_SCREEN_WIDTH) pega o valor da largura da tela do monitor e
	//   glutGet(GLUT_SCREEN_HEIGHT) Pega o valor da altura da tela
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)  - WINDOW_INITIAL_WIDTH )/2,
						   (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_INITIAL_HEIGHT)/2);
	glutCreateWindow("Reshape Window Size");


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}