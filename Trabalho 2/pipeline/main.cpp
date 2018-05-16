#include "main.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "objLoader.h"
#include "graphicpipeline.h"

objLoader *objData;

unsigned int screenWidth  = 512;
unsigned int screenHeigth = 512;

//-----------------------------------------------------------------------------
void display(void)
{
	// Vértice pertencente aos triangulos do arquivo .obj:
	float vertexObj[3][1];
	// Vértice após sua passagem pelo pipeline gráfico:
	float vertexPostPipeline[4][1];

	glViewport(0, 0, ViewPortWidth, ViewPortHeight);

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	for(int i=0; i<objData->faceCount; i++)
	{
		obj_face *o = objData->faceList[i];

		// Coordenadas de um vértice entregues pelo código de importação do .obj fornecido 
		// pelo professor
		vertexObj[0][1] = objData->vertexList[o->vertex_index[0]]->e[0]; // Coordenada X
		vertexObj[1][1] = objData->vertexList[o->vertex_index[0]]->e[1]; // Coordenada Y
		vertexObj[2][1] = objData->vertexList[o->vertex_index[0]]->e[2]; // Coordenada Z
		// Passando os vértices para o pipeline:
		pipeline(&vertexPostPipeline, vertexObj, screenWidth, screenHeigth);

		glVertex3f(	objData->vertexList[o->vertex_index[0]]->e[0], // primeira linha
					objData->vertexList[o->vertex_index[0]]->e[1],
					objData->vertexList[o->vertex_index[0]]->e[2]);
		glVertex3f(	objData->vertexList[o->vertex_index[1]]->e[0],
					objData->vertexList[o->vertex_index[1]]->e[1],
					objData->vertexList[o->vertex_index[1]]->e[2]);

		glVertex3f(	objData->vertexList[o->vertex_index[1]]->e[0],	// segunda linha
					objData->vertexList[o->vertex_index[1]]->e[1],
					objData->vertexList[o->vertex_index[1]]->e[2]);
		glVertex3f(	objData->vertexList[o->vertex_index[2]]->e[0],
					objData->vertexList[o->vertex_index[2]]->e[1],
					objData->vertexList[o->vertex_index[2]]->e[2]);

		glVertex3f(	objData->vertexList[o->vertex_index[2]]->e[0],	// terceira linha
					objData->vertexList[o->vertex_index[2]]->e[1],
					objData->vertexList[o->vertex_index[2]]->e[2]);
		glVertex3f(	objData->vertexList[o->vertex_index[0]]->e[0],
					objData->vertexList[o->vertex_index[0]]->e[1],
					objData->vertexList[o->vertex_index[0]]->e[2]);
	}

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	objData = new objLoader();
	objData->load("monkey_head2.obj");

	// Inicializações.
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeigth);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Trabalho 2 - Graphic Pipeline");

	// Passa a função que será exibida
	glutDisplayFunc(display);	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

