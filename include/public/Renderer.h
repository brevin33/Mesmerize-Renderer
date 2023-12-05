#pragma once
#include <Mesh.h>
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

    ObjectID addMesh(Mesh* mesh, std::string vertShaderFilePath, std::string fragShaderFilePath);

    enum GPUValueType {
        RGB32,
        RG32,
    };


}