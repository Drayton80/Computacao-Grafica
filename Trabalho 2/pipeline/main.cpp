#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	glBegin(GL_QUADS);                                          
        glVertex3f(-1.0f, 1.0f, 0.0f);                          // Top Left
        glVertex3f( 1.0f, 1.0f, 0.0f);                          // Top Right
        glVertex3f( 1.0f,-1.0f, 0.0f);                          // Bottom Right
        glVertex3f(-1.0f,-1.0f, 0.0f);                          // Bottom Left
    glEnd();	

    glTranslatef(0.5f,0.0f,0.0f);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

