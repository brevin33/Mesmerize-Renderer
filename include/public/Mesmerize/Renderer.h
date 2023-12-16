#pragma once
namespace MZ{
    //char* GraphicsAPI;
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "No Valid API"
#endif // VULKANRENDERER

    enum VertexValueType {
        R32G32B32 = VK_FORMAT_R32G32B32_SFLOAT,
        R32G32 = VK_FORMAT_R32G32_SFLOAT,
    };

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    ObjectID addObject(MeshID mesh, ShaderID shader, std::vector<TextureID>& textures);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint8_t numTextures, int uboSize, std::vector<VertexValueType>& VertexValues);

    MeshID createMesh(void* vertices, std::vector<uint32_t>& indices, uint32_t verticesSize, uint32_t vertexSize);

    TextureID createTexture(std::string textureFilepath);

    void updateUBO(ObjectID objectID, void* ubo);

}