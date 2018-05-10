#include <iostream>
#include <assimp>

int loadMesh(const std::string &file_name){
	std::ifstream fin(file_name.c_str());

	if(!fin.fail()){
		fin.close();
	}else{
		std::cerr << "Couldn't open file: " << file_name << std::endl;
		return EXIT_FAILURE;
	}

	Assimp::Importer assimp_importer;

	assimp_scene_ = assimp_importer.ReadFile(file_name, aiProcess_Triangulate);

	if(!assimp_scene_){
		srd::cerr << assimp_importer.GetErrorString() << std::endl;
		return EXIT_FAILURE;
	}

	if(assim_scene_->HasMeshes()){
		// Instanciando o Array de armazenamento, é um array bidimensional
		// 1ª Dimensão = Vertice; 2ª Dimensão = Coordenadas;
		float vertices[assimp_scene_->mNumVertices][3];

		for(unsigned int mesh_id = 0; mesh_id < assimp_scene_->mNumMeshes; mesh_id++){
			const aiMesh *mesh_ptr = assimp_scene_->mMeshes[mesh_id];

			// Auxiliar para guardar o vertex_id
			int point_id;

			for(unsigned int vertex_id = 0; vertex_id < mesh_ptr->mNumVertices; vertex_id += 3){
				const aiVector3D *vertex_ptr = &mesh_ptr->mVertices[vertex_id];

				//glm::dvec3 v0{ vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z };
				//glm::dvec3 v1{ vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z };
				//glm::dvec3 v2{ vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z };

				point_id = vertex_id;
				vertices[point_id][0] = vertex_ptr[0].x;
				vertices[point_id][1] = vertex_ptr[0].y;
				vertices[point_id][2] = vertex_ptr[0].z;

				point_id++;
				vertices[point_id][0] = vertex_ptr[1].x;
				vertices[point_id][1] = vertex_ptr[1].y;
				vertices[point_id][2] = vertex_ptr[1].z;

				point_id++;
				vertices[point_id][0] = vertex_ptr[2].x;
				vertices[point_id][1] = vertex_ptr[2].y;
				vertices[point_id][2] = vertex_ptr[2].z;				
			}
		}
	}

	return EXIT_FAILURE;
}