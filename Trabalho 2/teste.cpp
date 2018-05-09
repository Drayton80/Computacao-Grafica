#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

void division(int (*matrixResult)[4][4], int (*matrix)[4][4], int divider){
 	int lines  = sizeof (*matrix) / sizeof (*matrix)[0];  
  	int coluns = sizeof (*matrix)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		std::cout << "[ ";

		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;

			// Para testes:
			std::cout << (*matrixResult)[i][j];
		}

		// Para testes:
		std::cout << " ]\n";
	}
}

// Multiplica (m1*m2) duas matrizes passadas como parâmetros:
void multiplicationInteger(int (*matrixResult)[4][4], int (*matrix1)[4][4], int (*matrix2)[4][4]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int lines  = sizeof (*matrix1) / sizeof (*matrix1)[0];  
  	int coluns = sizeof (*matrix2)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		std::cout << "[ ";
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < coluns; k++){
				(*matrixResult)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
			}
			// Para testes:
			std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		std::cout << " ]\n";
	}
}

// Multiplica uma matriz com um vetor, ambos do tipo double:
void multiplicationInteger(int (*matrixResult)[4][1], int (*matrix)[4][4], int (*vector)[4][1]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int linesMatrix  = sizeof (*matrix) / sizeof (*matrix)[0];
 	int colunsMatrix = sizeof (*matrix)[0] / sizeof(int);  
  	int linesVector  = sizeof (*vector) / sizeof (*vector)[0];
 	int colunsVector = sizeof (*vector)[0] / sizeof(int); 

	for(int i = 0; i < linesMatrix; i++){
		std::cout << "[ ";
		for(int j = 0; j < colunsVector; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < colunsMatrix; k++){
				(*matrixResult)[i][j] += (*matrix)[i][k] * (*vector)[k][j];
			}
			// Para testes:
			std::cout << (*matrixResult)[i][j];
		}
		// Para testes:
		std::cout << " ]\n";
	}
}

int main(){
	int matrix1[4][4] = {{10, 2, 3, 5},
					   	 {0, 1, 0, 0},
					   	 {0, 0, 1, 0},
					   	 {0, 0, 0, 1}};

    int matrix2[4][4] = {{1, 0, 0, 0},
					   	 {1, 1, 0, 0},
					   	 {1, 0, 1, 0},
					   	 {1, 0, 0, 1}};

	int matrixResult[4][4];

	multiplicationInteger(&matrixResult, &matrix1, &matrix2);

	int matrix3[4][4] = {{1, 0, 0, 0},
					   	 {0, 2, 0, 0},
					   	 {0, 0, 3, 0},
					   	 {0, 0, 0, 4}};

    int matrix4[4][1] = {{1},
					   	 {1},
					   	 {1},
					   	 {1}};

	int matrixResult2[4][1];

	multiplicationInteger(&matrixResult2, &matrix3, &matrix4);
	

	int matrix5[4][4] = {{10, 10, 0, 0},
					   	 {0, 2, 0, 0},
					   	 {0, 2, 4, 4},
					   	 {0, 0, 0, 8}};


	int matrixResult3[4][4];

	int divider = 2;

	division(&matrixResult3, &matrix5, divider);
}
