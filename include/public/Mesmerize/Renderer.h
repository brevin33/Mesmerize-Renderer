#pragma once
namespace MZ{
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "No Valid API"

#endif // VULKANRENDERER

    BOOST_STRONG_TYPEDEF(uint32_t, InstanceID);
    BOOST_STRONG_TYPEDEF(uint16_t, ShaderID);
    BOOST_STRONG_TYPEDEF(uint16_t, MeshID);
    BOOST_STRONG_TYPEDEF(uint16_t, ObjectID);
    BOOST_STRONG_TYPEDEF(uint16_t, TextureID);
    BOOST_STRONG_TYPEDEF(uint16_t, MaterialID);
    BOOST_STRONG_TYPEDEF(uint16_t, UniformBufferID);

    struct RenderObject
    {
        ObjectID objectID;
        uint32_t instanceID;
    };
    enum VertexValueType {
        float3,
        float2,
        float4x4,
    };
    enum Mutability {
        CPU,
        GPU,
        BOTH,
    };


    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    RenderObject addObject(MeshID mesh, MaterialID material, void* instanceData, uint32_t instanceDataSize);

    MaterialID createMaterial(ShaderID shaderID, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers);

    MeshID createMesh(void* vertices, uint32_t* indices, uint32_t verticesSize, uint32_t vertexSize, uint32_t numIndices);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint32_t numTextures, uint32_t numBuffers, VertexValueType* VertexValues, uint32_t numVertexValues, VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    TextureID createTexture(std::string textureFilepath);

    UniformBufferID createMutUniformBuffer(void* data, uint32_t bufferSize, Mutability mutability);

    UniformBufferID createUniformBuffer(void* data, uint32_t bufferSize);

    void updateBuffer(UniformBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    void updateRenderObjectData(RenderObject renderObject, void* data, uint32_t dataSize);
}