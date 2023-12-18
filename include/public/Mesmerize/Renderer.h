#pragma once
namespace MZ{
    //char* GraphicsAPI;
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
    enum VertexValueType {
        R32G32B32 = VK_FORMAT_R32G32B32_SFLOAT,
        R32G32 = VK_FORMAT_R32G32_SFLOAT,
    };
#else
    #define GraphicsAPI "No Valid API"
    enum VertexValueType {
        R32G32B32,
        R32G32,
    };
#endif // VULKANRENDERER


    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    ObjectID addObject(MeshID mesh, MaterialID material);

    MaterialID createMaterial(void* materialProperties, int materialPropertiesSize, std::string* textures, uint8_t numTextures, std::string vertShaderPath, std::string fragShaderPath, VertexValueType* VertexValues, uint32_t numVertexValues);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint8_t numTextures, int uboSize, VertexValueType* VertexValues, uint32_t numVertexValues);

    MeshID createMesh(void* vertices, uint32_t* indices, uint32_t verticesSize, uint32_t vertexSize, uint32_t numIndices);

    TextureID createTexture(std::string textureFilepath);

}