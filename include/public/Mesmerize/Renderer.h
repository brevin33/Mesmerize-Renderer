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
    BOOST_STRONG_TYPEDEF(uint16_t, ComputeShaderID);
    BOOST_STRONG_TYPEDEF(uint16_t, ComputeID);



    enum VertexValueType {
        VTfloat4,
        VTfloat3,
        VTfloat2,
        VTfloat,
        VTfloat4x4,
        VTfloat4x3,
        VTfloat4x2,
        VTfloat3x4,
        VTfloat3x3,
        VTfloat3x2,
        VTfloat2x4,
        VTfloat2x3,
        VTfloat2x2,
    };

    void setup(GLFWwindow* window);

    void cleanup();

    void drawFrame();

    int getRenderWidth();

    int getRenderHeight();

    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, VertexBufferID instanceBuffer);

    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer);

    ComputeID addCompute(ComputeShaderID computeShader, uint32_t xDispatch, uint32_t yDispatch, uint32_t zDispatch, UniformBufferID* uniformBuffers, uint32_t numUniformBuffers, TextureID* textures, uint32_t numTextues, UniformBufferID* storageUniforms, uint32_t numStorageUniforms, VertexBufferID* storageVertex, uint32_t numStorageVertex, IndexBufferID* storageIndex, uint32_t numStorageIndex);

    MaterialID createMaterial(ShaderID shaderID, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers);

    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint32_t numTextures, uint32_t numBuffers, VertexValueType* VertexValues, uint32_t numVertexValues, VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    ComputeShaderID createComputeShader(std::string computeShaderPath, uint32_t numUniformBuffers, uint32_t numStaticTextures, uint32_t numStorageBuffers, uint32_t numStorageTextues);

    TextureID createTexture(std::string textureFilepath);

    VertexBufferID createVertexBuffer(void* vertices, uint32_t numVertices,uint64_t bufferSize);

    VertexBufferID createCPUMutVertexBuffer(void* vertices, uint32_t numVertices, uint32_t vertexSize, uint64_t bufferSize);

    VertexBufferID createGPUMutVertexBuffer(void* vertices, uint32_t numVertices, uint32_t vertexSize, uint64_t bufferSize);

    IndexBufferID createIndexBuffer(void* indices, uint64_t bufferSize);

    IndexBufferID createCPUMutIndexBuffer(void* indices, uint32_t numIndices, uint64_t bufferSize);

    IndexBufferID createGPUMutIndexBuffer(void* indices, uint32_t numIndices, uint64_t bufferSize);

    UniformBufferID createUniformBuffer(void* data, uint32_t bufferSize);

    UniformBufferID createCPUMutUniformBuffer(void* data, uint32_t bufferSize);

    UniformBufferID createGPUMutUniformBuffer(void* data, uint32_t bufferSize);

    void updateCPUMutUniformBuffer(UniformBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    void updateCPUMutVertexBuffer(VertexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    void updateCPUMutIndexBuffer(IndexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

}