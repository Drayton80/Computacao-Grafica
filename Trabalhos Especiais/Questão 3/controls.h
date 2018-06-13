#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "definitions.h"
#include "object.h"

#ifndef CONTROLS_H
#define CONTROLS_H

#define SPACE_BAR_KEY 32	// Código ASCII para a barra de espaço
#define ENTER_KEY 13        // Código ASCII para a tecla de Enter
#define ESC_KEY 27			// Código ASCII para a tecla de escape
#define TAB_KEY 9			// Código ASCII para a tecla de TAB
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53


/* Descrição: função criada para ser colocada como parâmetro de entrada
 * para a função glutKeyboardFunc() do Glut que registra as interações
 * das teclas padrões do teclado e faz com que sejam executadas quando 
 * pressionadas.
 *   Parâmetros de Entrada:
 *     key: Tecla pressionada;
 *     x: coordenada X atual do mouse no momento que a tecla hey foi pressionada.
 *     y: coordenada Y atual do mouse no momento que a tecla key foi pressionada.
 */
void keyboard (unsigned char key, int x, int y) {
    if (key == 'w'){
    	cameraRotationX += 2;
    }

    if(key == 's'){
    	cameraRotationX -= 2;
    }

    if(key == 'a'){
    	cameraRotationZ += 2;
    }

    if(key == 'd'){
    	cameraRotationZ -= 2;
    }

    if(key == 'q'){
    	cameraRotationY += 2;
    }

    if(key == 'e'){
    	cameraRotationY -= 2;
    }

    if(key == 'o'){
    	theta += 5;
    }

    if(key == '0'){
    	cubeRotationX = 0.0;
		cubeRotationY = 0.0;
		cubeRotationZ = 0.0; 
    }

    if(key == '1'){
    	cubeRotationY += 1;
        std::cout << "cubeRotationY: " << cubeRotationY << "\n";
    }

    if(key == '2'){
    	cubeRotationY -= 1;
        std::cout << "cubeRotationY: " << cubeRotationY << "\n";
    }

    if(key == '3'){
    	cubeRotationX += 1;
        std::cout << "cubeRotationX: " << cubeRotationX << "\n";
    }

    if(key == '4'){
    	cubeRotationZ += 1;
        std::cout << "cubeRotationZ: " << cubeRotationZ << "\n";
    }

    if(key == '5'){
    	cubeRotationZ -= 1;
        std::cout << "cubeRotationZ: " << cubeRotationZ << "\n";
    }
}

/* Descrição: função criada para ser colocada como parâmetro de entrada
 * para a função glutSpecialFunc() do Glut que registra as interações
 * das teclas especiais do teclado (como F1, seta para cima, etc) e faz 
 * com que sejam executadas quando pressionadas.
 *   Parâmetros de Entrada:
 *     key: Tecla especial pressionada;
 *     x: coordenada X atual do mouse no momento que a tecla hey foi pressionada.
 *     y: coordenada Y atual do mouse no momento que a tecla key foi pressionada.
 */
void keyboardSpecial (int key, int x, int y){
	if (key == GLUT_KEY_UP){
		cameraTranslationZ += 0.1;
	}

	if (key == GLUT_KEY_DOWN){
		cameraTranslationZ -= 0.1;
	}

	if (key == GLUT_KEY_RIGHT){
		cameraTranslationX -= 0.1;
	}

	if (key == GLUT_KEY_LEFT){
		cameraTranslationX += 0.1;
	}
}

/* Descrição: Passa as funções aqui criadas para suas respectivas chamadas nas funções
 * da biblioteca Glut.
 */
void controlsDefinitions(){
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
}

#endif	// CONTROLS_H

