#include <iostream>

#ifndef _MATRIXOPERATIONS_H_
#define _MATRIXOPERATIONS_H_

//#####################################-MULTIPLICATION-###########################################//
//---------------------------------------INTEGER-TYPES--------------------------------------------//
// Multiplica (m1*m2) duas matrizes passadas como parâmetros:
void multiplication(int (*matrixResult)[4][4], int (*matrix1)[4][4], int (*matrix2)[4][4]){
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

// Multiplica uma matriz com um vetor, ambos do tipo int:
void multiplication(int (*matrixResult)[4][1], int (*matrix)[4][4], int (*vector)[4][1]){
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
//------------------------------------------------------------------------------------------------//


//----------------------------------------FLOAT-TYPES---------------------------------------------//
// Multiplica (m1*m2) duas matrizes passadas como parâmetros:
void multiplication(float (*matrixResult)[4][4], float (*matrix1)[4][4], float (*matrix2)[4][4]){
	// A matriz resultante de uma multiplicação sempre tem o mesmo 
	// número de linhas de m1 e colunas de m2, em uma multiplicação
	// m1 * m2
 	int lines  = sizeof (*matrix1) / sizeof (*matrix1)[0];  
  	int coluns = sizeof (*matrix2)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		for(int j = 0; j < coluns; j++){
			// Inicializa o valor com 0 para poder fazer a soma do +=
			(*matrixResult)[i][j] = 0;
			
			for(int k = 0; k < coluns; k++){
				(*matrixResult)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
			}
		}
	}
}

// Multiplica uma matriz com um vetor, ambos do tipo float:
void multiplication(float (*matrixResult)[4][1], float (*matrix)[4][4], float (*vector)[4][1]){
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
//------------------------------------------------------------------------------------------------//
//################################################################################################//



//#########################################-DIVISION-#############################################//
//---------------------------------------INTEGER-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:
void division(int (*matrixResult)[4][4], int (*matrix)[4][4], int divider){
 	int lines  = sizeof (*matrix) / sizeof (*matrix)[0];  
  	int coluns = sizeof (*matrix)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;
		}
	}
}
//------------------------------------------------------------------------------------------------//

//-----------------------------------------FLOAT-TYPES--------------------------------------------//
// Divide uma matriz por uma constante:
void division(float (*matrixResult)[4][4], float (*matrix)[4][4], float divider){
 	int lines  = sizeof (*matrix) / sizeof (*matrix)[0];  
  	int coluns = sizeof (*matrix)[0] / sizeof(int);

	for(int i = 0; i < lines; i++){
		for(int j = 0; j < coluns; j++){
			(*matrixResult)[i][j] = (*matrix)[i][j] / divider;
		}
	}
}
//------------------------------------------------------------------------------------------------//
//################################################################################################//

#endif _MATRIXOPERATIONS_H_

