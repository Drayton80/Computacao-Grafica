#include <stdlib.h>		
#include <stdio.h>			
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int	window;	
int	Width;
int	Height;				

void InitGL(int Width, int Height){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();					// Reset The Projection Matrix

  glMatrixMode(GL_MODELVIEW);
}

void draw_world(void){
	// Define a cor de limpeza da tela como preto
	glClearColor(0.0, 0.0, 0.0, 1.0);
	// Limpa o color buffer e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
}

void show_world(void){

	draw_world();

}


int main(int argc, char *argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/* get a 640 x 480 window */
    glutInitWindowSize(640, 480);

	/*	The window starts at the upper left corner of the screen	*/
	/*	Aparentemente esta funcao so faz sentido no X-Windows. Em	*/
	/*	MS-Windows a janela aparece sempre aa esquerda em cima de	*/
	/*	qualquer forma.												*/
	glutInitWindowPosition(0, 0);  

	/* Abrimos aqui uma janela, Open a window						*/ 
	/* A variavel window guarda o numero da janela. Pode ser util.	*/
    glutCreateWindow("UFPB - ICG - Atividade II");

	/*	Register the function to do all our OpenGL drawing.			*/
    glutDisplayFunc(draw_world);

	/* Register the function called when the keyboard is pressed.	*/
	//glutKeyboardFunc(tecla);

	/* Resgitramos a funcao que é chamada quando uma tecla especial */
	/* foi teclada, como setas e teclas de funcao.					*/
	//glutSpecialFunc(teclas_de_seta);
	
	
	/* Funcao chamada sempre que o Loop do GLUT esta ocioso			*/
	/* Esta funcao eh responsavel pelos efeitos de animacao.		*/
	//glutIdleFunc(show_world);

	/* Chamamos a funcao que realiza o resto das inicializacoes.	*/
	InitGL( 640, 480);

    /* Iniciamos a maquina de processamento de eventos do GLUT.		*/  
	glutMainLoop();
    return (0);
    }


