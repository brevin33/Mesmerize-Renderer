#pragma once
namespace MZ{
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "No Valid API"

#endif // VULKANRENDERER

    BOOST_STRONG_TYPEDEF(uint16_t, ShaderID);
    BOOST_STRONG_TYPEDEF(uint16_t, RenderObjectID);
    BOOST_STRONG_TYPEDEF(uint16_t, TextureID);
    BOOST_STRONG_TYPEDEF(uint16_t, MaterialID);
    BOOST_STRONG_TYPEDEF(uint16_t, UniformBufferID);
    BOOST_STRONG_TYPEDEF(uint16_t, VertexBufferID);
    BOOST_STRONG_TYPEDEF(uint16_t, IndexBufferID);

    enum VertexValueType {
        float3,
        float2,
        float4x4,
    };

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    int getRenderWidth();

    int getRenderHeight();

    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, VertexBufferID instanceBuffer);

    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer);

    MaterialID createMaterial(ShaderID shaderID, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint32_t numTextures, uint32_t numBuffers, VertexValueType* VertexValues, uint32_t numVertexValues, VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    TextureID createTexture(std::string textureFilepath);

    VertexBufferID createVertexBuffer(void* vertices, uint32_t numVertices,uint64_t bufferSize);

    VertexBufferID createCPUMutVertexBuffer(void* vertices, uint32_t numVertices, uint32_t vertexSize, uint64_t bufferSize);

    IndexBufferID createIndexBuffer(void* indices, uint64_t bufferSize);

    IndexBufferID createCPUMutIndexBuffer(void* indices, uint32_t numIndices, uint64_t bufferSize);

    UniformBufferID createCPUMutUniformBuffer(void* data, uint32_t bufferSize);

    UniformBufferID createUniformBuffer(void* data, uint32_t bufferSize);

    void updateCPUMutUniformBuffer(UniformBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    void updateCPUMutVertexBuffer(VertexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    void updateCPUMutIndexBuffer(IndexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

}