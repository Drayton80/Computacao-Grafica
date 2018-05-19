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
	float vertexObj1[3][1];
    float vertexObj2[3][1];
    float vertexObj3[3][1];
	// Vértice após sua passagem pelo pipeline gráfico:
	float vertexPostPipeline1[4][1];
    float vertexPostPipeline2[4][1];
    float vertexPostPipeline3[4][1];

	glViewport(0, 0, screenWidth, screenHeigth);

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	for(int i=0; i < 20; i++)
	{
		obj_face *o = objData->faceList[i];

		// Coordenadas de um vértice entregues pelo código de importação do .obj fornecido
		// pelo professor
		vertexObj1[0][1] = objData->vertexList[o->vertex_index[0]]->e[0]; // Coordenada X
		vertexObj1[1][1] = objData->vertexList[o->vertex_index[0]]->e[1]; // Coordenada Y
		vertexObj1[2][1] = objData->vertexList[o->vertex_index[0]]->e[2]; // Coordenada Z

		vertexObj2[0][1] = objData->vertexList[o->vertex_index[3]]->e[0]; // Coordenada X
		vertexObj2[1][1] = objData->vertexList[o->vertex_index[3]]->e[1]; // Coordenada Y
		vertexObj2[2][1] = objData->vertexList[o->vertex_index[3]]->e[2]; // Coordenada Z

		vertexObj3[0][1] = objData->vertexList[o->vertex_index[6]]->e[0]; // Coordenada X
		vertexObj3[1][1] = objData->vertexList[o->vertex_index[6]]->e[1]; // Coordenada Y
		vertexObj3[2][1] = objData->vertexList[o->vertex_index[6]]->e[2]; // Coordenada Z

		// Passando os vértices para o pipeline:
		pipeline(&vertexPostPipeline1, vertexObj1, screenWidth, screenHeigth);
        pipeline(&vertexPostPipeline2, vertexObj2, screenWidth, screenHeigth);
        pipeline(&vertexPostPipeline3, vertexObj3, screenWidth, screenHeigth);

        // Definindo a coloração:
        TypeColor c1;
        c1.R = 0;
        c1.G = 0;
        c1.B = 0;
        c1.A = 255;

        TypePixel p1, p2, p3;

        p1.pX = vertexPostPipeline1[0][1];
        p1.pY = vertexPostPipeline1[1][1];

        p2.pX = vertexPostPipeline2[0][1];
        p2.pY = vertexPostPipeline2[1][1];

        p3.pX = vertexPostPipeline3[0][1];
        p3.pY = vertexPostPipeline3[1][1];

		DrawTriangle(p1, p2, p3);
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

