#pragma once
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Mesmerize/Renderer.h>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	bool operator==(const Vertex& other) const {
		return Position == other.Position;
	}

	static std::vector<MZ::VertexValueType> getVertexValueTypes() {
		std::vector<MZ::VertexValueType> types(5);
		types[0] = MZ::float3;
		types[1] = MZ::float3;
		types[2] = MZ::float2;
		types[3] = MZ::float3;
		types[4] = MZ::float3;
		return types;
	}
};


class Model {
public:
	Model(std::string modelFilePath);
	void unload();
	std::vector<MZ::RenderObject> Model::addToRenderer();
	std::vector<std::vector<Vertex>> modelVertices; 
	std::vector<std::vector<uint32_t>> modelIndices;
	std::vector<std::vector<std::string>> modelTextures;
	std::vector<uint32_t> assimpMaterialID;
	std::vector<MZ::MeshID> meshIDs;
	std::vector<MZ::MaterialID> materialIDs;

private:

	std::string directory;
	std::unordered_map<uint32_t, MZ::MaterialID> modelMaterialToMaterial;
	void processNode(aiNode* node, const aiScene* scene);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::string> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
