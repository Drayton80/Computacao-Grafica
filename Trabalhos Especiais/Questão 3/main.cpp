#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "controls.h"
#include "definitions.h"
#include "controls.h"

using namespace std;

Object *cube = new Object();

void camera (void) {
	glTranslatef(cameraTranslationX-1.0f, -1.0f, cameraTranslationZ-5.0f);

	glRotatef(cameraRotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(cameraRotationZ, 0.0f, 0.0f, 1.0f);
}

void reshape (int width, int height) {  
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);   
	glMatrixMode(GL_PROJECTION);   
	glLoadIdentity();   

	// Define as opções da perspectiva, como a Field of View, o near plane, etc
	gluPerspective(30, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
	glMatrixMode(GL_MODELVIEW);   
}

void drawAxis(){
	// Eixo X:
	glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINES); 
        glVertex3f( 0.0f, 0.0f, 0.0f);   
        glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();

    // Eixo Y:
	glColor3f (0.0, 1.0, 0.0);
    glBegin(GL_LINES); 
        glVertex3f(0.0f,  0.0f, 0.0f);   
        glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();

    // Eixo Z:
	glColor3f (0.0, 0.0, 1.0);
    glBegin(GL_LINES); 
        glVertex3f(0.0f, 0.0f,  0.0f);   
        glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();
}


void display(void){
	// Define a cor de limpeza do color buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Limpa o color buffer e o depth buffer com a cor indicada:
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Carrega a matriz identidade no conjunto de matrizes para
	// poder limpar as matrizes de mudança
	glLoadIdentity();

	camera();

	drawAxis();

	cube->setRotationAngleX(cubeRotationX);
	cube->setRotationAngleY(cubeRotationY);
	cube->setRotationAngleZ(cubeRotationZ);

	cube->generate(1.0f, 1.0f, 1.0f);
    
    // Troca os buffers
    glutSwapBuffers();
}

int main (int argumentsC, char **argumentsV){
	// Inicialização do Glut (definitions.h)
	initializations(argumentsC, argumentsV);

	// Passa a display tanto para glutDisplayFunc quanto para
	// a glutIdleFunc, pois, pelas minhas pesquisas em tutoriais,
	// forçar essa chamada tanto em Display quanto em Idle gera uma
	// pequena melhora de performance no desempenho da aplicação com glut
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);

    // Chama a função do header controls.h que define as teclas que
    // serão usadas e o que farão ao serem pressionadas
    controlsDefinitions();

    // Inicia o loop de renderização
    glutMainLoop ();

    return 0;
}