#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Mesmerize/Renderer.h>

class Model {
public:
	Model(std::string modelFilePath);
	void unload();
	std::vector<ObjectID> Model::addToRenderer(ShaderID shaderID);
	std::vector<std::vector<MZ::Vertex>> modelVertices; 
	std::vector<std::vector<uint32_t>> modelIndices;
	std::vector<std::vector<std::string>> modelTextures;
	std::vector<MeshID> meshIDs;
	std::vector<std::vector<TextureID>> textureIDs;

private:

	std::string directory;
	std::unordered_map<std::string, TextureID> filePathToTexture;
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::string> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
