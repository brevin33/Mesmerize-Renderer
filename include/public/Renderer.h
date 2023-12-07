#pragma once
#include <Mesh.h>
#include <Model.h>
namespace MZ{
    //char* GraphicsAPI;
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "Vulkan"
#endif // VULKANRENDERER

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    std::vector<ObjectID> addModel(Model model, std::string vertShaderFilePath, std::string fragShaderFilePath);

    ObjectID addMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::string vertShaderFilePath, std::string fragShaderFilePath, std::vector<std::string> textures = std::vector<std::string>(0));

    enum GPUValueType {
        RGB32,
        RG32,
    };


}