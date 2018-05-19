#include <math.h>
#include "matrixoperations.h"

#ifndef _GRAPHIC_PIPELINE_H_
#define _GRAPHIC_PIPELINE_H_

// Aplica a Matriz Model à um vetor passado como entrada para passar do espaço do objeto para o
// espaço do universo
void mModel(double (*vectorWorldSpace)[4][1], double (*vectorObjectSpace)[4][1]){

	double matrixModel [4][4] = {{ 1,  0,  0,  0},
							    { 0,  1,  0,  0},
							    { 0,  0,  1, -2},
							    { 0,  0,  0,  1}};

    // Transformação do espaço de objeto para o do universo:
    std::cout << "\n @@ Aplicação da Matrix Model @@ \n";
	multiplication(vectorWorldSpace, &matrixModel, vectorObjectSpace);
}

// Cálcula os vetores da base da camera (eixo x, y e z de canera), constroem ela e, através da mesma,
// geram a Matriz View para passar do espaço do universo para o de camera
void mView(double (*vectorCameraSpace)[4][1], double (*vectorWorldSpace)[4][1],
				   double lookAt[3], double up[3], double cameraPosition[3]){

	// EIXO Z DA CAMERA:
	// Construindo o vetor no formato utilizado em matrixoperations.h:
	double dVector[3][1] = {{lookAt[0] - cameraPosition[0]},
						   {lookAt[1] - cameraPosition[1]},
						   {lookAt[2] - cameraPosition[2]}};
	// Obtendo o módulo do vetor d (direction):
	double moduloVetor = sqrt((dVector[0][0]*dVector[0][0]) + (dVector[1][0]*dVector[1][0]) + (dVector[2][0]*dVector[2][0]));
	std::cout << "dVector[0][0]: " << (dVector[0][0]*dVector[0][0]) << " = " << dVector[0][0] << " * " << dVector[0][0] << "\n";
	std::cout << "dVector[1][0]: " << (dVector[1][0]*dVector[1][0]) << " = " << dVector[1][0] << " * " << dVector[1][0] << "\n";
	std::cout << "dVector[2][0]: " << (dVector[2][0]*dVector[2][0]) << " = " << dVector[2][0] << " * " << dVector[2][0] << "\n";
	std::cout << "Modulo do Vetor = " << moduloVetor << "\n";
	// vetor referente ao eixo z da camera:
	double zCamera[3][1]; 
	// zc = - (d/|d|)
	std::cout << "Divisão do zCamera: \n";
	division(&zCamera, &dVector, moduloVetor);
	zCamera[0][0] = -zCamera[0][0];
	zCamera[1][0] = -zCamera[1][0];
	zCamera[2][0] = -zCamera[2][0];

	// EIXO X DA CAMERA:
	// Instanciando o vetor up
	double vetorUp[3][1]  = {{up[0]},
						    {up[1]},
						    {up[2]}};
    // Vetor que resulta do produto vetorial:
	double vetorProdutoVetorial[3][1];
	std::cout << "Produto vetorial para o xCamera: \n";
	produtoVetorial(&vetorProdutoVetorial, vetorUp, zCamera);

	// Se a coordenada estiver abaixo de 1e-160 (valor aproximado) e acima de 0, sua multiplicação ao quadrado
	// (feita no moduloVetor) resultaria em 0 devido ao tão baixo valor que ultrapassaria o
	// limite suportado de um double, resultando em uma posterior divisão por 0 para gerar
	// o vetor unitário. Isso é uma contramedida feita para contornar isso e limitar os valores
	if((1e-160 > vetorProdutoVetorial[0][0]) && (vetorProdutoVetorial[0][0] > 0) ){
		vetorProdutoVetorial[0][0] = 1e-160;
	}
	if((1e-160 > vetorProdutoVetorial[1][0]) && (vetorProdutoVetorial[1][0] > 0) ){
		vetorProdutoVetorial[1][0] = 1e-160;
	}
	if((1e-160 > vetorProdutoVetorial[2][0]) && (vetorProdutoVetorial[2][0] > 0) ){
		vetorProdutoVetorial[2][0] = 1e-160;
	}
	// A mesma coisa ocorre com valores acima de -1e-160 (aproximado) e abaixo de 0
	if((-1e-160 < vetorProdutoVetorial[0][0]) && (vetorProdutoVetorial[0][0] < 0) ){
		vetorProdutoVetorial[0][0] = -1e-160;
	}
	if((-1e-160 < vetorProdutoVetorial[1][0]) && (vetorProdutoVetorial[1][0] < 0) ){
		vetorProdutoVetorial[1][0] = -1e-160;
	}
	if((-1e-160 < vetorProdutoVetorial[2][0]) && (vetorProdutoVetorial[2][0] < 0) ){
		vetorProdutoVetorial[2][0] = -1e-160;
	}

	// Pegando o módulo desse vetor para poder fazer o eixo unitário:
	std::cout << "vetorProdutoVetorial[0][0] = " << vetorProdutoVetorial[0][0] << "\n";
	std::cout << "vetorProdutoVetorial[1][0] = " << vetorProdutoVetorial[1][0] << "\n";
	std::cout << "vetorProdutoVetorial[2][0] = " << vetorProdutoVetorial[2][0] << "\n";
	moduloVetor = sqrt((vetorProdutoVetorial[0][0]*vetorProdutoVetorial[0][0]) + 
					   (vetorProdutoVetorial[1][0]*vetorProdutoVetorial[1][0]) + 
					   (vetorProdutoVetorial[2][0]*vetorProdutoVetorial[2][0]));

	// Essa condição foi necessária pois há momentos em que os valores das coordenadas do vetorProdutoVetorial
	// são tá pequenas (ex.: 3.1e-307) que quando elevados ao quadrado dentro do cálculo para o moduloVetor resultam
	// em 0, fazendo com que moduloVetor acabe recebendo 0 e, assim, posteriormente quando dividimos o vetorProdutoVetorial
	// por moduloVetor acabe resultando no valor "nan", não desejado
	//if(moduloVetor == 0){
	//	moduloVetor = 2.2e-322;
	//}

	std::cout << "vetorProdutoVetorial[0][0]²: " << (vetorProdutoVetorial[0][0]*vetorProdutoVetorial[0][0]) << " = " 
												 << vetorProdutoVetorial[0][0] << " * " << vetorProdutoVetorial[0][0] 
												 << "\n";
	std::cout << "vetorProdutoVetorial[1][0]²: " << (vetorProdutoVetorial[1][0]*vetorProdutoVetorial[1][0]) << " = " 
												 << vetorProdutoVetorial[1][0] << " * " << vetorProdutoVetorial[1][0] 
												 << "\n";
	std::cout << "vetorProdutoVetorial[2][0]²: " << (vetorProdutoVetorial[2][0]*vetorProdutoVetorial[2][0]) << " = " 
												 << vetorProdutoVetorial[2][0] << " * " << vetorProdutoVetorial[2][0] 
												 << "\n";
	std::cout << "Modulo do Vetor = " << moduloVetor << "\n";
	// Vetor referente ao eixo x da camera:
	double xCamera[3][1];
	// xc = (ucXzc)/|ucXzc|
	std::cout << "Divisão do xCamera: \n";
	division(&xCamera, &vetorProdutoVetorial, moduloVetor);

	// EIXO Y DA CAMERA:
    // Vetor que resulta do produto vetorial:
    std::cout << "Produto vetorial do yCamera: \n";
	produtoVetorial(&vetorProdutoVetorial, zCamera, xCamera);

	// Se a coordenada estiver abaixo de 1e-160 (valor aproximado) e acima de 0, sua multiplicação ao quadrado
	// (feita no moduloVetor) resultaria em 0 devido ao tão baixo valor que ultrapassaria o
	// limite suportado de um double, resultando em uma posterior divisão por 0 para gerar
	// o vetor unitário. Isso é uma contramedida feita para contornar isso e limitar os valores
	if((1e-160 > vetorProdutoVetorial[0][0]) && (vetorProdutoVetorial[0][0] > 0) ){
		vetorProdutoVetorial[0][0] = 1e-160;
	}
	if((1e-160 > vetorProdutoVetorial[1][0]) && (vetorProdutoVetorial[1][0] > 0) ){
		vetorProdutoVetorial[1][0] = 1e-160;
	}
	if((1e-160 > vetorProdutoVetorial[2][0]) && (vetorProdutoVetorial[2][0] > 0) ){
		vetorProdutoVetorial[2][0] = 1e-160;
	}
	// A mesma coisa ocorre com valores acima de -1e-160 (aproximado) e abaixo de 0
	if((-1e-160 < vetorProdutoVetorial[0][0]) && (vetorProdutoVetorial[0][0] < 0) ){
		vetorProdutoVetorial[0][0] = -1e-160;
	}
	if((-1e-160 < vetorProdutoVetorial[1][0]) && (vetorProdutoVetorial[1][0] < 0) ){
		vetorProdutoVetorial[1][0] = -1e-160;
	}
	if((-1e-160 < vetorProdutoVetorial[2][0]) && (vetorProdutoVetorial[2][0] < 0) ){
		vetorProdutoVetorial[2][0] = -1e-160;
	}

	// Pegando o módulo desse vetor para poder fazer o eixo unitário:
	moduloVetor = sqrt((vetorProdutoVetorial[0][0]*vetorProdutoVetorial[0][0]) + 
					   (vetorProdutoVetorial[1][0]*vetorProdutoVetorial[1][0]) + 
					   (vetorProdutoVetorial[2][0]*vetorProdutoVetorial[2][0]));

	// Essa condição foi necessária pois há momentos em que os valores das coordenadas do vetorProdutoVetorial
	// são tá pequenas (ex.: 3.1e-307) que quando elevados ao quadrado dentro do cálculo para o moduloVetor resultam
	// em 0, fazendo com que moduloVetor acabe recebendo 0 e, assim, posteriormente quando dividimos o vetorProdutoVetorial
	// por moduloVetor acabe resultando no valor "nan", não desejado
	//if(moduloVetor == 0){
	//	moduloVetor = 2.2e-300;
	//}
	// Vetor referente ao eixo y da camera:
	double yCamera[3][1];
	// xc = (ucXzc)/|ucXzc|
	std::cout << "Divisão do yCamera: \n";
	division(&yCamera, &vetorProdutoVetorial, moduloVetor);

	// CONSTRUINDO A MATRIX VIEW:
	double matrixBt [4][4] = {{ xCamera[0][0],  xCamera[1][0],  xCamera[2][0],  0},
							 { yCamera[0][0],  yCamera[1][0],  yCamera[2][0],  0},
							 { zCamera[0][0],  zCamera[1][0],  zCamera[2][0],  0},
							 {       0      ,        0      ,        0      ,  1}};

	double matrixTrasposicao [4][4] = {{ 1,  0,  0, -cameraPosition[0]},
	   						          { 0,  1,  0, -cameraPosition[1]},
							    	  { 0,  0,  1, -cameraPosition[2]},
							    	  { 0,  0,  0,          1        }};

   	double matrixView[4][4];

   	multiplication(&matrixView, &matrixBt, &matrixTrasposicao);

   	// transformação do espaço do universo para o de camera:
   	std::cout << "\n @@ Aplicação da Matrix View @@ \n";
   	multiplication(vectorCameraSpace, &matrixView, vectorWorldSpace);

}

// Os parâmetros de entrada são uma matriz que será alterada para representar o vetor no espaço de recorte,
// uma matriz que será o vetor no espaço de camera e um d que representa a distância do centro focal até
// a o near plane.  
void mProjection(double (*vectorClippingSpace)[4][1], double (*vectorCameraSpace)[4][1], double d){
	// Essa é uma matriz de translação que leva o centro focal para a origem	
	double matrixT [4][4] = {{ 1,  0,  0,  0},
						    { 0,  1,  0,  0},
						    { 0,  0,  1,  d},
						    { 0,  0,  0,  1}};

    // Essa matriz efetivamente aplica a distorção projetiva
    double matrixP [4][4] = {{ 1,  0,  0 ,  0},
						    { 0,  1,  0 ,  0},
						    { 0,  0,  1 ,  0},
						    { 0,  0,-1/d,  1}};

  	// Para obter a matriz de projeção basta multiplicar uma matriz
    // pela outra e, assim, combiná-las
    double matrixProjection[4][4];
    std::cout << "Combinação das Matrizes P e T: \n";
    multiplication(&matrixProjection, &matrixP, &matrixT);

    // por fim, aplica-se a transformação do espaço de camera para o de recorte
    std::cout << "\n @@ Aplicação da Matrix Projection @@ \n";
	multiplication(vectorClippingSpace, &matrixProjection, vectorCameraSpace);
}

// Recebe a largura e altura de tela, assim como as coordenadas do ponto no espaço 
// canonico, e, através disso, aplica a matriz view port para passar do espaço canônico
// para o espaço de tela
void mViewPort(double (*vectorScreenSpace)[4][1], double (*vectorCanonicalSpace)[4][1], 
			   int w, int h){
	// É preciso fazer uma escala e inverter o Y da imagem pois usualmente o pixel
	// 0,0 da tela fica no canto superior esquerdo (em vez do inferior esquerdo, como
	// era nos demais espaços que trabalhamos até agora)	
	double matrixInvertion [4][4] = {{  1,  0,  0,  0},
						    		{  0, -1,  0,  0},
						    		{  0,  0,  1,  0},
						    		{  0,  0,  0,  1}};

    // Também é necessário escalar a imagem para que se adeque ao tamanho
	// da tela (representado pelos parâmetros w(width) e h(height))
    double matrixScale [4][4] = {{ w/2,   0,  0,  0},
						    	{   0, h/2,  0,  0},
						    	{   0,   0,  1,  0},
						    	{   0,   0,  0,  1}};

	// Por fim é preciso transladar para mover os pontos para não ficarem na
    // na origem como centro
    double matrixTranslation [4][4] = {{  1,  0,  0, (w-1)/2},
						    		  {  0,  1,  0, (h-1)/2},
						    		  {  0,  0,  1,     0  },
						    		  {  0,  0,  0,     1  }};


  	// Para obter a matriz view port basta multiplicar as matrizes obtidas
    double matrixViewPort[4][4];
    double auxMatrixVP[4][4];
    std::cout << "Multiplicação da matrixScale e matrixInvertion: \n";
    multiplication(&auxMatrixVP, &matrixScale, &matrixInvertion);
    std::cout << "Multiplicação da matrixTranslation e matrixVP: \n";
    multiplication(&matrixViewPort, &matrixTranslation, &auxMatrixVP);

    // por fim, aplica-se a transformação do espaço canonico para o de tela
    std::cout << "\n @@ Aplicação da Matrix View Port @@ \n";
	multiplication(vectorScreenSpace, &matrixViewPort, vectorCanonicalSpace);
}

// Esse pipeline faz a passagem dos vertices dos triângulos para o espaço de tela
// sem aplicar uma multiplicação para condensar as matrizes de cada passagem de espaço
// em uma só
void pipeline(double (*output)[4][1], double (*input)[3][1], int width, int height){
	double    verticesObjectSpace[4][1],    verticesWorldSpace[4][1],
		     verticesCameraSpace[4][1], verticesClippingSpace[4][1],
		  verticesCanonicalSpace[4][1];
	double cameraPosition[3] = {0, 0, 1};
	double lookAt[3] 		= {0, 0, 0};
	double up[3] 			= {0, 1, 0};
	double homogeneosCoordinate = 1;
	double distanceNearPlane = 1;
	

	// Aqui transformamos os pontos para o espaço homogêneo:
	for(int i = 0; i <= 2; i++){
		verticesObjectSpace[i][1] = (*input)[i][1] * homogeneosCoordinate;
	}
	// Adicionando a coordenada homogênea:
	verticesObjectSpace[3][1] = homogeneosCoordinate;

	// Aplicando a matrix model:
	std::cout << "Iniciando mModel: \n";
	mModel(&verticesWorldSpace, &verticesObjectSpace);
	// Aplicando a matrix view:
	std::cout << "Iniciando mView: \n";
	mView(&verticesCameraSpace, &verticesWorldSpace, lookAt, up, cameraPosition);
	// Aplicando a matrix projection:
	std::cout << "Iniciando mProjection: \n";
	mProjection(&verticesClippingSpace, &verticesCameraSpace, distanceNearPlane);
	// Em seguida é preciso dividir os valores pela coordenada homogênea que leva para
	// o espaço canônico
	std::cout << "Iniciando divisão do espaço Canônico: \n";
	division(&verticesCanonicalSpace, &verticesClippingSpace, -1/distanceNearPlane);
	// Por fim, apenas foi necessário passar pelo último estágio do pipeline ao aplicar
	// a matriz view port
	std::cout << "Iniciando mViewPort: \n";
	mViewPort(output, &verticesCanonicalSpace, width, height);
}

#endif // _GRAPHIC_PIPELINE_H_

