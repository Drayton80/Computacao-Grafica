#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define WINDOW_INITIAL_WIDTH 1024
#define WINDOW_INITIAL_HEIGHT 768

int window_width;
int window_height;

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float lastx, lasty;

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0); 
    glRotatef(yrot,0.0,1.0,0.0);  
    glTranslated(-xpos,-ypos,-zpos);
}

void display(void){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)window_width/(GLfloat)window_height, 1.0, 16.0);

	camera();

	glTranslatef(0.0f, -0.5f, -3.0f);

	int maxAndMinLines = 100;

	for(int i = -maxAndMinLines; i <= maxAndMinLines; i += 1){
		glBegin(GL_LINES);
			// Linhas Horizontais:
			glColor3f (0.4f, 0.4f, 0.4f);
			glVertex3f(-100.0f, -0.5f, i);
			glVertex3f( 100.0f, -0.5f, i);

			// Linhas Verticais:
			glColor3f (0.4f, 0.4f, 0.4f);
			glVertex3f( i, -0.5f, -100.0f);
			glVertex3f( i, -0.5f,  100.0f);			
		glEnd();
	}

	//glLoadIdentity();

	//gluPerspective(60.0, (GLfloat)window_width/(GLfloat)window_height, 1.0, 16.0);

	glTranslatef(0.0f, 0.5f, -3.0f);

	glColor3f (0.4f, 0.0f, 0.0f);
	glutSolidCube(0.5); 

	/*
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
	*/

	glFlush();
}

void reshape(int width, int height){
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);

	window_width  = width;
	window_height = height;

	glLoadIdentity();
	//gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
    if (key == 'q')
    {
    	xrot += 1;
    	if (xrot >360) xrot -= 360;
    }

    if (key == 'z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key== 'w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='d')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos += float(cos(yrotrad)) * 0.2;
    zpos += float(sin(yrotrad)) * 0.2;
    }

    if (key=='a')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xpos -= float(cos(yrotrad)) * 0.2;
    zpos -= float(sin(yrotrad)) * 0.2;
    }

    if (key==27)
    {
    exit(0);
    }

}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the 
    int diffy=y-lasty; //check the difference between the 
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the addition
    yrot += (float) diffx;    //set the xrot to yrot with the addition
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

	glutPassiveMotionFunc(mouseMovement);


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);

	glutMainLoop();
}