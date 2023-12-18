#include "Model.h"

void Model::unload() {
    modelVertices.clear();
    modelIndices.clear();
    modelTextures.clear();
    meshIDs.clear();
    materialIDs.clear();
};

Model::Model(std::string modelFilePath) {
	modelVertices = std::vector<std::vector<Vertex>>(0);
	modelIndices = std::vector<std::vector<uint32_t>>(0);
	modelTextures = std::vector<std::vector<std::string>>(0);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    directory = modelFilePath.substr(0, modelFilePath.find_last_of('/')) + '/';

    processNode(scene->mRootNode, scene);

    materialIDs.resize(modelVertices.size());
    meshIDs.resize(modelVertices.size());
    for (size_t i = 0; i < modelVertices.size(); i++)
    {
        materialIDs[i] = modelMaterialToMaterial[assimpMaterialID[i]];
        meshIDs[i] = MZ::createMesh(modelVertices[i].data(), modelIndices[i].data(), modelVertices[i].size(), sizeof(modelVertices[i][0]), modelIndices[i].size());
    }
}

std::vector<MZ::RenderObject> Model::addToRenderer() {
    std::vector<MZ::RenderObject> ids(meshIDs.size());
    for (size_t i = 0; i < ids.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        ids[i] = MZ::addObject(meshIDs[i], materialIDs[i], &model, sizeof(glm::mat4));
    }
    return ids;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

void Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::string> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    modelVertices.push_back(vertices);
    modelIndices.push_back(indices);
    modelTextures.push_back(textures);
    assimpMaterialID.push_back(mesh->mMaterialIndex);

    if (modelMaterialToMaterial.find(mesh->mMaterialIndex) != modelMaterialToMaterial.end()) return;

    // 1. diffuse maps
    std::vector<std::string> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    //std::vector<std::string> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    //std::vector<std::string> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    //std::vector<std::string> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    MZ::VertexValueType instanceType = MZ::float4x4;

    glm::vec3 color = glm::vec3(1, 1, 1);
    modelMaterialToMaterial[mesh->mMaterialIndex] = MZ::createMaterial("../../../shaders/unlitVert.spv", "../../../shaders/unlitFrag.spv" , &color, sizeof(glm::vec3), textures.data(), textures.size(), Vertex::getVertexValueTypes().data(), Vertex::getVertexValueTypes().size(), &instanceType, 1);
}

std::vector<std::string> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<std::string> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        textures.push_back(directory + str.C_Str());
    }
    return textures;
}

