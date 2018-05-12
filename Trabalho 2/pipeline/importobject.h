#include <iostream>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/camera.h>
#include <assimp/config.h>
#include <assimp/Defines.h>
#include <assimp/Exporter.hpp>
#include <assimp/mesh.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/ai_assert.h>
#include <assimp/camera.h>
#include <assimp/metadata.h>

using namespace std;

/*
int loadObject(){
	const aiScene* scene = aiImportFile("/home/drayton/Área de Trabalho/Computação Gráfica/Computacao-Grafica/Trabalho 2/Codes/monkey_head3.obj", aiProcessPreset_TargetRealtime_MaxQuality);
}

int main(){

}
*/

/*	Descrição: pega o arquivo .obj que será analisado e retorna o número de vertices dentro dele
 */
int fileNumberMeshes(const std::string &file_name){
	std::ifstream fin(file_name.c_str());

	if(!fin.fail()){
		fin.close();
	}else{
		std::cerr << "Couldn't open file: " << file_name << std::endl;
		return EXIT_FAILURE;
	}

	Assimp::Importer assimp_importer;
	const aiScene *assimp_scene_ = assimp_importer.ReadFile(file_name, aiProcess_Triangulate);
	// Cria um ponteiro que aponta para a mesh indicada (apenas serve para apenas uma mesh)
	const aiMesh *mesh_ptr = assimp_scene_->mMeshes[0];

	if(!assimp_scene_){
		std::cerr << assimp_importer.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}

	// Retorna o número de vértices dentro da mesh apontada
	return mesh_ptr->mNumVertices;
}


int loadMesh(const std::string &file_name, float (*vertices)[][3]){
	std::ifstream fin(file_name.c_str());

	if(!fin.fail()){
		fin.close();
	}else{
		std::cerr << "Couldn't open file: " << file_name << std::endl;
		return EXIT_FAILURE;
	}

	Assimp::Importer assimp_importer;

	const aiScene* assimp_scene_ = assimp_importer.ReadFile(file_name, aiProcess_Triangulate);

	if(!assimp_scene_){
		std::cerr << assimp_importer.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}

	if(assimp_scene_->HasMeshes()){
		for(unsigned int mesh_id = 0; mesh_id < assimp_scene_->mNumMeshes; mesh_id++){
			const aiMesh *mesh_ptr = assimp_scene_->mMeshes[mesh_id];

			int aux_vertex_id;

			for(unsigned int vertex_id = 0; vertex_id < mesh_ptr->mNumVertices; vertex_id += 3){
				const aiVector3D *vertex_ptr = &mesh_ptr->mVertices[vertex_id];

				aux_vertex_id = vertex_id;

				//glm::dvec3 v0{ vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z };
				//glm::dvec3 v1{ vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z };
				//glm::dvec3 v2{ vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z };

				// Vertice 1 do enésimo (aux_vertex_id) triângulo
				vertices[aux_vertex_id][0] = vertex_ptr[0].x;
				vertices[aux_vertex_id][1] = vertex_ptr[0].y;
				vertices[aux_vertex_id][2] = vertex_ptr[0].z;
				aux_vertex_id++;
				// Vertice 2 do enésimo (aux_vertex_id) triângulo
				vertices[aux_vertex_id][0] = vertex_ptr[1].x;
				vertices[aux_vertex_id][1] = vertex_ptr[1].y;
				vertices[aux_vertex_id][2] = vertex_ptr[1].z;
				aux_vertex_id++;
				// Vertice 3 do enésimo (aux_vertex_id) triângulo
				vertices[aux_vertex_id][0] = vertex_ptr[2].x;
				vertices[aux_vertex_id][1] = vertex_ptr[2].y;
				vertices[aux_vertex_id][2] = vertex_ptr[2].z;
			}
		}
	}

	return EXIT_FAILURE;
}
