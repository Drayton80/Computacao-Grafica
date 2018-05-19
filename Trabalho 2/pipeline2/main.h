#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "definitions.h"
#include "mygl.h"

GLuint tex;

void (*DrawFunc)(void);


//*****************************************************************************
void exitprog(void)
{
	// Libera a memória referente ao framebuffer.
	if (!FBptr)
		delete [] FBptr;

	std::clog << "Exiting...\n";
}

//*****************************************************************************
void InitOpenGL(int *argc, char **argv)
{
	glutInit(argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Trabalho 2 - Pipeline");
	

}

//*****************************************************************************
void InitCallBacks(void)
{
	atexit( exitprog );
	//glutDisplayFunc(display);
}

//*****************************************************************************
void InitDataStructures(void)
{
	// Aloca o framebuffer e inicializa suas posições com 0.
	FBptr = new unsigned char[IMAGE_WIDTH * IMAGE_HEIGHT * 5];
	
	for (unsigned int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT ; i++)
	{
		FBptr[i*4]   = 0;
		FBptr[i*4+1] = 0;
		FBptr[i*4+2] = 0;
		FBptr[i*4+3] = 255;
	}
}

