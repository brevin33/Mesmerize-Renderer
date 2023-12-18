#pragma once
namespace MZ{
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
    enum VertexValueType {
        float3 = VK_FORMAT_R32G32B32_SFLOAT,
        float2 = VK_FORMAT_R32G32_SFLOAT,
        float4x4,
    };
#else
    #define GraphicsAPI "No Valid API"
    enum VertexValueType {
        R32G32B32,
        R32G32,
    };
#endif // VULKANRENDERER

#define InstanceID uint32_t
#define ShaderID uint16_t
#define MeshID uint16_t
#define ObjectID uint16_t
#define TextureID uint16_t
#define MaterialID uint16_t

    struct RenderObject {
        ObjectID objectID;
        uint32_t instanceID;
    };

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    RenderObject addObject(MeshID mesh, MaterialID material, void* instanceData, uint32_t instanceDataSize);

    MaterialID createMaterial(std::string vertShaderPath, std::string fragShaderPath, void* materialProperties, int materialPropertiesSize, std::string* textures, uint8_t numTextures, VertexValueType* VertexTypes, uint32_t numVertexTypes, VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    MeshID createMesh(void* vertices, uint32_t* indices, uint32_t verticesSize, uint32_t vertexSize, uint32_t numIndices);

}