#pragma once
#include <Mesmerize/Vertex.h>
namespace MZ{
    //char* GraphicsAPI;
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "No Valid API"
#endif // VULKANRENDERER

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    ObjectID addObject(MeshID mesh, ShaderID shader, std::vector<TextureID>& textures);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint8_t numTextures);

    MeshID createMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    TextureID createTexture(std::string textureFilepath);


    enum GPUValueType {
        RGB32,
        RG32,
    };


}