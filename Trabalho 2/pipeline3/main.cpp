#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "objLoader.h"
#include "graphicpipeline.h"
#include "definitions.h"
#include "mygl.h"
#include "main.h"

// Ponteiro para o objeto que carregará o modelo 3D (formato OBJ).
objLoader *objData;

unsigned int ViewPortWidth  = 512;
unsigned int ViewPortHeight = 512;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	/*	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glFlush();
	*/

	// ###################################################################### //
	// #######################// EXIBINDO OS EIXOS \\######################## //

	TypeColor colorAxisX;
    colorAxisX.R = 255;
    colorAxisX.G = 0;
    colorAxisX.B = 0;
    colorAxisX.A = 255;

    TypeColor colorAxisY;
    colorAxisY.R = 0;
    colorAxisY.G = 255;
    colorAxisY.B = 0;
    colorAxisY.A = 255;

    TypeColor colorAxisZ;
    colorAxisZ.R = 0;
    colorAxisZ.G = 0;
    colorAxisZ.B = 255;
    colorAxisZ.A = 255;

    // Vértice pertencente aos eixos X, Y e Z:
    double originPoint[3][1] = {{0},
    				  		    {0},
    						    {0}};

    double axisPointX[3][1] = {{1},
    						   {0},
    						   {0}};

    double axisPointY[3][1] = {{0},
    						   {1},
    						   {0}};

    double axisPointZ[3][1] = {{0},
    						   {0},
    						   {1}};

    // Pontos após sua passagem pelo pipeline gráfico:
    double originPostPipeline[4][1];
    double xPostPipeline[4][1];
    double yPostPipeline[4][1];
    double zPostPipeline[4][1];

    // Passando os vértices para o pipeline:
    //| std::cout << "Chegou até o pipeline \n";
    pipeline(&originPostPipeline, &originPoint, IMAGE_WIDTH, IMAGE_HEIGHT);
    pipeline(&xPostPipeline		, &axisPointX , IMAGE_WIDTH, IMAGE_HEIGHT);
    pipeline(&yPostPipeline		, &axisPointY , IMAGE_WIDTH, IMAGE_HEIGHT);
    pipeline(&zPostPipeline		, &axisPointZ , IMAGE_WIDTH, IMAGE_HEIGHT);

    TypePixel origin, axisX, axisY, axisZ;

    origin.pX 	 = (int) originPostPipeline[0][0];
    origin.pY 	 = (int) originPostPipeline[1][0];
    origin.color = colorAxisX;

    axisX.pX 	= (int) xPostPipeline[0][0];
    axisX.pY 	= (int) xPostPipeline[1][0];
    axisX.color = colorAxisX;

    axisY.pX 	= (int) yPostPipeline[0][0];
    axisY.pY 	= (int) yPostPipeline[1][0];
    axisY.color = colorAxisY;

    axisZ.pX 	= (int) zPostPipeline[0][0];
    axisZ.pY 	= (int) zPostPipeline[1][0];
    axisZ.color = colorAxisZ;	

    std::cout << "Chegou até o DrawLine X \n";
    //DrawLine(origin, axisX);
    std::cout << "Chegou até o DrawLine Y \n";
    //DrawLine(origin, axisY);
    std::cout << "Chegou até o DrawLine Z \n";
    //DrawLine(origin, axisZ);	

	// ######################\\-------------------//######################### //
	// ###################################################################### //

	// Vértice pertencente aos triangulos do arquivo .obj:
    double vertexObj1[3][1];
    double vertexObj2[3][1];
    double vertexObj3[3][1];
    // Vértice após sua passagem pelo pipeline gráfico:
    double vertexPostPipeline1[4][1];
    double vertexPostPipeline2[4][1];
    double vertexPostPipeline3[4][1];

    //| std::cout << "Iniciando o FOR \n";
	//| std::cout << "Entrou no GLLines \n";
	for(int i=0; i<objData->faceCount; i++){
	    //| std::cout << "\n\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&" << (i+1) << "ª Iteração do For &&&&&&&&&&&&&&&&&&&&&&&&& \n";
	    //| std::cout << "Pegando o objeto \n";
	    obj_face *o = objData->faceList[i];

	    // Coordenadas de um vértice entregues pelo código de importação do .obj fornecido
	    // pelo professor
	    //| std::cout << "Chegou até os vértices \n";
	    //| std::cout << "1 \n";
	    vertexObj1[0][0] = objData->vertexList[o->vertex_index[0]]->e[0]; // Coordenada X
	    vertexObj1[1][0] = objData->vertexList[o->vertex_index[0]]->e[1]; // Coordenada Y
	    vertexObj1[2][0] = objData->vertexList[o->vertex_index[0]]->e[2]; // Coordenada Z
	    //| std::cout << "2\n";
	    vertexObj2[0][0] = objData->vertexList[o->vertex_index[1]]->e[0]; // Coordenada X
	    vertexObj2[1][0] = objData->vertexList[o->vertex_index[1]]->e[1]; // Coordenada Y
	    vertexObj2[2][0] = objData->vertexList[o->vertex_index[1]]->e[2]; // Coordenada Z
	    //| std::cout << "3 \n";
	    vertexObj3[0][0] = objData->vertexList[o->vertex_index[2]]->e[0]; // Coordenada X
	    vertexObj3[1][0] = objData->vertexList[o->vertex_index[2]]->e[1]; // Coordenada Y
	    vertexObj3[2][0] = objData->vertexList[o->vertex_index[2]]->e[2]; // Coordenada Z

	    // Passando os vértices para o pipeline:
	    //| std::cout << "Chegou até o pipeline \n";
	    pipeline(&vertexPostPipeline1, &vertexObj1, IMAGE_WIDTH, IMAGE_HEIGHT);
	    pipeline(&vertexPostPipeline2, &vertexObj2, IMAGE_WIDTH, IMAGE_HEIGHT);
	    pipeline(&vertexPostPipeline3, &vertexObj3, IMAGE_WIDTH, IMAGE_HEIGHT);

	    // Definindo a coloração:
	    //| std::cout << "Chegou até as cores \n";
	    TypeColor c1;
	    c1.R = 0;
	    c1.G = 0;
	    c1.B = 255;
	    c1.A = 255;

	    TypePixel p1, p2, p3;

	    //| std::cout << "Instanciou os pontos \n";
	    p1.pX = (int) vertexPostPipeline1[0][0];
	    p1.pY = (int) vertexPostPipeline1[1][0];
	    p1.color = c1;		

	    p2.pX = (int) vertexPostPipeline2[0][0];
	    p2.pY = (int) vertexPostPipeline2[1][0];
	    p2.color = c1;
		
	    p3.pX = (int) vertexPostPipeline3[0][0];
	    p3.pY = (int) vertexPostPipeline3[1][0];
	    p3.color = c1;

	    /*
	    glBegin(GL_TRIANGLES);

		    glColor3f(0.5,0,0);

		    glVertex2f(vertexPostPipeline1[0][0], vertexPostPipeline1[1][0]);
		    glVertex2f(vertexPostPipeline2[0][0], vertexPostPipeline2[1][0]);
		    glVertex2f(vertexPostPipeline3[0][0], vertexPostPipeline3[1][0]);

	    glEnd();
		*/

	    //| std::cout << "Desenhou os pontos \n";
	    DrawTriangle(p1, p2, p3);
	    //| std::cout << "Terminou de desenhar \n";
	}

	//glDisable(GL_TEXTURE_2D);

	/*
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	*/
}

//-----------------------------------------------------------------------------
// Funcao que imprime as coordenadas de um vertice. 
// Pode ser utilizada para fazer debug de código.
void printVector(obj_vector *v)
{
	printf("%.2f,", v->e[0] );
	printf("%.2f,", v->e[1] );
	printf("%.2f  ", v->e[2] );
}

//-----------------------------------------------------------------------------
// Esta funcao apenas imprime informacoes referentes ao modelo que foi carregado, 
// tais como numero de vertices, normais, fontes de luz, etc.
void PrintModelInfo(objLoader* ptr)
{
	printf("Number of vertices: %i\n", ptr->vertexCount);
	printf("Number of vertex normals: %i\n", ptr->normalCount);
	printf("Number of texture coordinates: %i\n", ptr->textureCount);
	printf("\n");
	
	printf("Number of faces: %i\n", ptr->faceCount);
	for(int i=0; i<ptr->faceCount; i++)
	{
		obj_face *o = ptr->faceList[i];
		printf(" face ");
		for(int j=0; j<3; j++)
		{
			printVector(ptr->vertexList[ o->vertex_index[j] ]);
		}
		printf("\n");
	}

	printf("\n");
	
	printf("Number of spheres: %i\n", ptr->sphereCount);
	for(int i=0; i<ptr->sphereCount; i++)
	{
		obj_sphere *o = ptr->sphereList[i];
		printf(" sphere ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->up_normal_index ]);
		printVector(ptr->normalList[ o->equator_normal_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of planes: %i\n", ptr->planeCount);
	for(int i=0; i<ptr->planeCount; i++)
	{
		obj_plane *o = ptr->planeList[i];
		printf(" plane ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->normal_index]);
		printVector(ptr->normalList[ o->rotation_normal_index]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of point lights: %i\n", ptr->lightPointCount);
	for(int i=0; i<ptr->lightPointCount; i++)
	{
		obj_light_point *o = ptr->lightPointList[i];
		printf(" plight ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of disc lights: %i\n", ptr->lightDiscCount);
	for(int i=0; i<ptr->lightDiscCount; i++)
	{
		obj_light_disc *o = ptr->lightDiscList[i];
		printf(" dlight ");
		printVector(ptr->vertexList[ o->pos_index ]);
		printVector(ptr->normalList[ o->normal_index ]);
		printf("\n");
	}

	printf("\n");
	
	printf("Number of quad lights: %i\n", ptr->lightQuadCount);
	for(int i=0; i<ptr->lightQuadCount; i++)
	{
		obj_light_quad *o = ptr->lightQuadList[i];
		printf(" qlight ");
		printVector(ptr->vertexList[ o->vertex_index[0] ]);
		printVector(ptr->vertexList[ o->vertex_index[1] ]);
		printVector(ptr->vertexList[ o->vertex_index[2] ]);
		printVector(ptr->vertexList[ o->vertex_index[3] ]);
		printf("\n");
	}

	printf("\n");
	
	if(ptr->camera != NULL)
	{
		printf("Found a camera\n");
		printf(" position: ");
		printVector(ptr->vertexList[ ptr->camera->camera_pos_index ]);
		printf("\n looking at: ");
		printVector(ptr->vertexList[ ptr->camera->camera_look_point_index ]);
		printf("\n up normal: ");
		printVector(ptr->normalList[ ptr->camera->camera_up_norm_index ]);
		printf("\n");
	}

	printf("\n");

	printf("Number of materials: %i\n", ptr->materialCount);
	for(int i=0; i<ptr->materialCount; i++)
	{
		obj_material *mtl = ptr->materialList[i];
		printf(" name: %s", mtl->name);
		printf(" amb: %.2f ", mtl->amb[0]);
		printf("%.2f ", mtl->amb[1]);
		printf("%.2f\n", mtl->amb[2]);

		printf(" diff: %.2f ", mtl->diff[0]);
		printf("%.2f ", mtl->diff[1]);
		printf("%.2f\n", mtl->diff[2]);

		printf(" spec: %.2f ", mtl->spec[0]);
		printf("%.2f ", mtl->spec[1]);
		printf("%.2f\n", mtl->spec[2]);
		
		printf(" reflect: %.2f\n", mtl->reflect);
		printf(" trans: %.2f\n", mtl->trans);
		printf(" glossy: %i\n", mtl->glossy);
		printf(" shiny: %i\n", mtl->shiny);
		printf(" refact: %.2f\n", mtl->refract_index);

		printf(" texture: %s\n", mtl->texture_filename);
		printf("\n");
	}

	printf("\n");
	
	//vertex, normal, and texture test
	if(ptr->textureCount > 2 && ptr->normalCount > 2 && ptr->faceCount > 2)
	{
		printf("Detailed face data:\n");

		for(int i=0; i<3; i++)
		{
			obj_face *o = ptr->faceList[i];
			printf(" face ");
			for(int j=0; j<3; j++)
			{
				printf("%i/", o->vertex_index[j] );
				printf("%i/", o->texture_index[j] );
				printf("%i ", o->normal_index[j] );
			}
			printf("\n");
		}
	}
}

//-----------------------------------------------------------------------------
// Libera a memoria do objeto responsavel por guardar dados do modelo.
void FreeMemFunc(void)
{
	std::clog << "Exiting...\n";

	if (!objData)
		delete objData;
}

//-----------------------------------------------------------------------------
// Programa principal
int main(int argc, char **argv)
{
	objData = new objLoader();			// cria o objeto que carrega o modelo
	objData->load("monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
										// Neste caso, deve ser sempre do tipo OBJ.

	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	DrawFunc = MyGlDraw;
	//glutDisplayFunc(display);
	// Habilite esta função se você deseja imprimir na tela dados do modelo
	// gerados durante a sua carga.
	//PrintModelInfo(objData);

	//atexit(FreeMemFunc);

	glutMainLoop();

	return 0;
}

