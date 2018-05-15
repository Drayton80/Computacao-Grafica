#ifndef _GRAPHIC_PIPELINE_H_
#define _GRAPHIC_PIPELINE_H_

#include <math.h>
#include "graphicpipeline.h"
#include "matrixoperations.h"

// Aplica a Matriz Model à um vetor passado como entrada para passar do espaço do objeto para o
// espaço do universo
void mModel(float (*vectorWorldSpace)[4][1], float vectorObjectSpace[4][1]){
	float matrixModel [4][4] = {{ 1,  0,  0,  0},
							    { 0,  1,  0,  0},
							    { 0,  0,  1, -2},
							    { 0,  0,  0,  1}};

    // Transformação do espaço de objeto para o do universo:
	multiplication(vectorWorldSpace, matrixModel, vectorObjectSpace);
}

// Cálcula os vetores da base da camera (eixo x, y e z de canera), constroem ela e, através da mesma,
// geram a Matriz View para passar do espaço do universo para o de camera
void mView(float (*vectorCameraSpace)[4][1], float vectorWorldSpace[4][1],
				   float lookAt[3], float up[3], float cameraPosition[3]){

	// EIXO Z DA CAMERA:
	// Construindo o vetor no formato utilizado em matrixoperations.h:
	float dVector[3][1] = {{lookAt[0] - cameraPosition[0]},
						   {lookAt[1] - cameraPosition[1]},
						   {lookAt[2] - cameraPosition[2]}};
	// Obtendo o módulo do vetor d (direction):
	float moduloVetor = sqrt((lookAt[0]*lookAt[0]) + (lookAt[1]*lookAt[1]) + (lookAt[2]*lookAt[2]));
	// vetor referente ao eixo z da camera:
	float zCamera[3][1]; 
	// zc = - (d/|d|)
	division(&zCamera, dVector, moduloVetor);
	zCamera[0][1] = -zCamera[0][1];
	zCamera[1][1] = -zCamera[1][1];
	zCamera[2][1] = -zCamera[2][1];

	// EIXO X DA CAMERA:
	// Instanciando o vetor up
	float vetorUp[3][1]  = {{up[0]},
						    {up[1]},
						    {up[2]}};
    // Vetor que resulta do produto vetorial:
	float vetorProdutoVetorial[3][1];
	produtoVetorial(&vetorProdutoVetorial, vetorUp, zCamera);
	// Pegando o módulo desse vetor para poder fazer o eixo unitário:
	moduloVetor = sqrt((vetorProdutoVetorial[0][1]*vetorProdutoVetorial[0][1]) + 
					   (vetorProdutoVetorial[1][1]*vetorProdutoVetorial[1][1]) + 
					   (vetorProdutoVetorial[2][1]*vetorProdutoVetorial[2][1]));
	// Vetor referente ao eixo x da camera:
	float xCamera[3][1];
	// xc = (ucXzc)/|ucXzc|
	division(&xCamera, vetorProdutoVetorial, moduloVetor);

	// EIXO Y DA CAMERA:
    // Vetor que resulta do produto vetorial:
	produtoVetorial(&vetorProdutoVetorial, zCamera, xCamera);
	// Pegando o módulo desse vetor para poder fazer o eixo unitário:
	moduloVetor = sqrt((vetorProdutoVetorial[0][1]*vetorProdutoVetorial[0][1]) + 
					   (vetorProdutoVetorial[1][1]*vetorProdutoVetorial[1][1]) + 
					   (vetorProdutoVetorial[2][1]*vetorProdutoVetorial[2][1]));
	// Vetor referente ao eixo y da camera:
	float yCamera[3][1];
	// xc = (ucXzc)/|ucXzc|
	division(&yCamera, vetorProdutoVetorial, moduloVetor);

	// CONSTRUINDO A MATRIX VIEW:
	float matrixBt [4][4] = {{ xCamera[0][1],  xCamera[1][1],  xCamera[2][1],  0},
							 { yCamera[0][1],  yCamera[1][1],  yCamera[2][1],  0},
							 { zCamera[0][1],  zCamera[1][1],  zCamera[2][1],  0},
							 {       0      ,        0      ,        0      ,  1}};

	float matrixTrasposicao [4][4] = {{ 1,  0,  0, -cameraPosition[0]},
	   						          { 0,  1,  0, -cameraPosition[1]},
							    	  { 0,  0,  1, -cameraPosition[2]},
							    	  { 0,  0,  0,          1        }};

   	float matrixView[4][4];

   	multiplication(&matrixView, matrixBt, matrixTrasposicao);

   	// transformação do espaço do universo para o de camera:
   	multiplication(vectorCameraSpace, matrixView, vectorWorldSpace);

}

// Os parâmetros de entrada são uma matriz que será alterada para representar o vetor no espaço de recorte,
// uma matriz que será o vetor no espaço de camera e um d que representa a distância do centro focal até
// a o near plane.  
void mProjection(float (*vectorClippingSpace)[4][1], float vectorCameraSpace[4][1], float d){
	// Essa é uma matriz de translação que leva o centro focal para a origem	
	float matrixT [4][4] = {{ 1,  0,  0,  0},
						    { 0,  1,  0,  0},
						    { 0,  0,  1,  d},
						    { 0,  0,  0,  1}};

    // Essa matriz efetivamente aplica a distorção projetiva
    float matrixP [4][4] = {{ 1,  0,  0 ,  0},
						    { 0,  1,  0 ,  0},
						    { 0,  0,  1 ,  0},
						    { 0,  0,-1/d,  1}};

  	// Para obter a matriz de projeção basta multiplicar uma matriz
    // pela outra e, assim, combiná-las
    float matrixProjection[4][4];
    multiplication(&matrixProjection, matrixP, matrixT);

    // por fim, aplica-se a transformação do espaço de camera para o de recorte
	multiplication(vectorClippingSpace, matrixProjection, vectorCameraSpace);
}

// Recebe a largura e altura de tela, assim como as coordenadas do ponto no espaço 
// canonico, e, através disso, aplica a matriz view port para passar do espaço canônico
// para o espaço de tela
void mViewPort(float (*vectorScreenSpace)[4][1], float vectorCanonicalSpace[4][1], 
			   int w, int h){
	// É preciso fazer uma escala e inverter o Y da imagem pois usualmente o pixel
	// 0,0 da tela fica no canto superior esquerdo (em vez do inferior esquerdo, como
	// era nos demais espaços que trabalhamos até agora)	
	float matrixInvertion [4][4] = {{  1,  0,  0,  0},
						    		{  0, -1,  0,  0},
						    		{  0,  0,  1,  0},
						    		{  0,  0,  0,  1}};

    // Também é necessário escalar a imagem para que se adeque ao tamanho
	// da tela (representado pelos parâmetros w(width) e h(height))
    float matrixScale [4][4] = {{ w/2,   0,  0,  0},
						    	{   0, h/2,  0,  0},
						    	{   0,   0,  1,  0},
						    	{   0,   0,  0,  1}};

	// Por fim é preciso transladar para mover os pontos para não ficarem na
    // na origem como centro
    float matrixTranslation [4][4] = {{  1,  0,  0, (w-1)/2},
						    		  {  0,  1,  0, (h-1)/2},
						    		  {  0,  0,  1,     0  },
						    		  {  0,  0,  0,     1  }};


  	// Para obter a matriz view port basta multiplicar as matrizes obtidas
    float matrixViewPort[4][4];
    float auxMatrixVP[4][4];
    multiplication(&auxMatrixVP, matrixScale, matrixInvertion);
    multiplication(&matrixViewPort, matrixTranslation, auxMatrixVP);

    // por fim, aplica-se a transformação do espaço canonico para o de tela
	multiplication(vectorScreenSpace, matrixViewPort, vectorCanonicalSpace);
}

// Esse pipeline faz a passagem dos vertices dos triângulos para o espaço de tela
// sem aplicar uma multiplicação para condensar as matrizes de cada passagem de espaço
// em uma só
void pipeline(float (*output)[4][1], float (*input)[3][1], int width, int height){
	float    verticesObjectSpace[4][1],    verticesWorldSpace[4][1],
		     verticesCameraSpace[4][1], verticesClippingSpace[4][1],
		  verticesCanonicalSpace[4][1],   verticesScreenSpace[4][1];
	float cameraPosition[3] = {0, 0, 2};
	float lookAt[3] 		= {0, 0,-2};
	float up[3] 			= {0, 1, 0};
	float homogeneosCoordinate = 1;
	float distanceNearPlane = 1;
	

	// Aqui transformamos os pontos para o espaço homogêneo:
	for(int i = 0; i <= 2; i++){
		verticesObjectSpace[i][1] = (*input)[i][1] * homogeneosCoordinate;
	}
	// Adicionando a coordenada homogênea:
	verticesObjectSpace[3][1] = homogeneosCoordinate;

	// Aplicando a matrix model:
	mModel(&verticesWorldSpace, verticesObjectSpace);
	// Aplicando a matrix view:
	mView(&verticesCameraSpace, verticesWorldSpace, lookAt, up, cameraPosition);
	// Aplicando a matrix projection:
	mProjection(&verticesClippingSpace, verticesCameraSpace, distanceNearPlane);
	// Em seguida é preciso dividir os valores pela coordenada homogênea que leva para
	// o espaço canônico
	division(&verticesCanonicalSpace, verticesClippingSpace, -1/distanceNearPlane);
	// Por fim, apenas foi necessário passar pelo último estágio do pipeline ao aplicar
	// a matriz view port
	mViewPort(&verticesScreenSpace, verticesCanonicalSpace, width, height);
}

#endif // _GRAPHIC_PIPELINE_H_

