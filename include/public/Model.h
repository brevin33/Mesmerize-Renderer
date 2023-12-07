#pragma once
#include <string>
#include <vector>
#include <Vertex.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace MZ {

	class Model {
	public:
		Model(std::string modelFilePath);
		std::vector<std::vector<Vertex>> modelVertices; 
		std::vector<std::vector<uint32_t>> modelIndices;
		std::vector<std::vector<std::string>> modelTextures;

	private:

		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<std::string> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
