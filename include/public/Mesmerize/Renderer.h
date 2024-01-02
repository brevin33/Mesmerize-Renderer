#pragma once
namespace MZ{
#ifdef VULKANRENDERER
    #define GraphicsAPI "Vulkan"
#else
    #define GraphicsAPI "No Valid API"

#endif // VULKANRENDERER

#define MAX_COMMANDS 1024

    BOOST_STRONG_TYPEDEF(uint16_t, ShaderID);
    BOOST_STRONG_TYPEDEF(uint16_t, RenderObjectID);
    BOOST_STRONG_TYPEDEF(uint16_t, TextureID);
    BOOST_STRONG_TYPEDEF(uint16_t, MaterialID);
    BOOST_STRONG_TYPEDEF(uint16_t, UniformBufferID);
    BOOST_STRONG_TYPEDEF(uint16_t, VertexBufferID);
    BOOST_STRONG_TYPEDEF(uint16_t, IndexBufferID);
    BOOST_STRONG_TYPEDEF(uint16_t, ComputeShaderID);
    BOOST_STRONG_TYPEDEF(uint16_t, ComputeID);

    // negitive radius means no culling
    struct BoundingSphere {
        BoundingSphere(glm::vec3 positon, float radius) {
            sphereInfo = glm::vec4(positon,radius);
        }
        glm::vec4 sphereInfo;
    };

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

    /// <summary>
    /// must call before doing anything can optionally use setupNoDefaults
    /// </summary>
    /// <param name="window"> surface to render to </param>
    void setup(GLFWwindow* window, int numGBuffers, std::string pathToRendererDir);

    /// <summary>
    /// setup but this has no default buffers for stuff like culling
    /// </summary>
    /// <param name="window"> surface to render to </param>
    void setupNoDefaults(GLFWwindow* window, int numGColorBuffers, std::string pathToRendererDir);

    /// <summary>
    /// call when you no longer want to render or at end of program
    /// </summary>
    void cleanup();

    /// <summary>
    /// call whenver a new frame needs to be drawn
    /// </summary>
    void drawFrame();

    /// <summary>
    /// gets the resultion of the rendered output image width
    /// </summary>
    int getRenderWidth();

    /// <summary>
    /// gets the resultion of the rendered output image height
    /// </summary>
    int getRenderHeight();

    /// <summary>
    /// must call before calling drawFrame. sets the deffered shader
    /// </summary>
    void setDefferedShader(std::string fragShader, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers);

    /// <summary>
    /// Call once then an object will be rendered every drawFrame
    /// </summary>
    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer);
    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, VertexBufferID instanceBuffer);
    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, BoundingSphere boundingSphere);
    RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, VertexBufferID instanceBuffer, BoundingSphere boundingSphere);

    /// <summary>
    /// Call once then this compute shader will be called every frame
    /// </summary>
    ComputeID addCompute(ComputeShaderID computeShader, uint32_t xDispatch, uint32_t yDispatch, uint32_t zDispatch, UniformBufferID* uniformBuffers, uint32_t numUniformBuffers, TextureID* textures, uint32_t numTextues,
        UniformBufferID* storageUniforms, uint32_t numStorageUniforms, VertexBufferID* storageVertex, uint32_t numStorageVertex, IndexBufferID* storageIndex, uint32_t numStorageIndex, bool hasDrawCommandBuffer = false);

    /// <summary>
    /// Material defines the shader as well as all binding related to it
    /// </summary>
    MaterialID createMaterial(ShaderID shaderID, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers);

    /// <summary>
    /// a vert and fragment shader. multiple materials cand be created from a single shader
    /// </summary>
    ShaderID createShader(std::string vertShaderPath, std::string fragShaderPath, uint32_t maxNumberOfMaterial, uint32_t numTextures, uint32_t numBuffers, VertexValueType* VertexValues, uint32_t numVertexValues,
        VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    /// <summary>
    /// a compute shader this can be dispached in multiple way by adding a compute.
    /// </summary>
    ComputeShaderID createComputeShader(std::string computeShaderPath, uint32_t maxNumberOfComputes, uint32_t numUniformBuffers, uint32_t numStaticTextures, uint32_t numStorageBuffers,
        uint32_t numStorageTextues, bool hasDrawCommandBuffer = false);

    /// <summary>
    /// loads a texture to be used by other parts of the renderer
    /// </summary>
    TextureID createTexture(std::string textureFilepath);

    /// <summary>
    /// a vertex buffer can hold vertex data or instance data. you must specify the types of mutability by calling the right constructor
    /// </summary>
    VertexBufferID createConstVertexBuffer(void* vertices, uint32_t numVertices,uint64_t bufferSize);
    VertexBufferID createCPUMutVertexBuffer(void* vertices, uint32_t numVertices, uint32_t vertexSize, uint64_t bufferSize);
    VertexBufferID createGPUMutVertexBuffer(void* vertices, uint32_t numVertices, uint32_t vertexSize, uint64_t bufferSize);

    /// <summary>
    /// a index buffer can hold indexs connecting vertices. you must specify the types of mutability by calling the right constructor
    /// </summary>
    IndexBufferID createConstIndexBuffer(void* indices, uint64_t bufferSize);
    IndexBufferID createCPUMutIndexBuffer(void* indices, uint32_t numIndices, uint64_t bufferSize);
    IndexBufferID createGPUMutIndexBuffer(void* indices, uint32_t numIndices, uint64_t bufferSize);

    /// <summary>
    /// a uniform buffer can be made to pass information in to shaders. you must specify the types of mutability by calling the right constructor
    /// </summary>
    UniformBufferID createConstUniformBuffer(void* data, uint32_t bufferSize);
    UniformBufferID createCPUMutUniformBuffer(void* data, uint32_t dataSize, uint32_t bufferSize);
    UniformBufferID createGPUMutUniformBuffer(void* data, uint32_t dataSize, uint32_t bufferSize);


    /// <summary>
    /// Deletes The Resource
    /// </summary>
    void deleteResourceCPU(UniformBufferID id);
    void deleteResourceConst(UniformBufferID id);
    void deleteResourceGPU(UniformBufferID id);
    void deleteResourceGPU(VertexBufferID id);
    void deleteResourceCPU(VertexBufferID id);
    void deleteResourceConst(VertexBufferID id);
    void deleteResourceConst(IndexBufferID id);
    void deleteResourceCPU(IndexBufferID id);
    void deleteResourceGPU(IndexBufferID id);
    void deleteResource(RenderObjectID id);
    void deleteResource(ComputeID id);
    void deleteResource(ShaderID id);
    void deleteResource(ComputeShaderID id);
    void deleteResource(TextureID id);
    void deleteResource(MaterialID id);


    /// <summary>
    /// update a part or all of a buffer. must be CPUMutable buffer or will crash
    /// </summary>
    void updateCPUMutUniformBuffer(UniformBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);
    void updateCPUMutVertexBuffer(VertexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);
    void updateCPUMutIndexBuffer(IndexBufferID buffer, void* data, uint32_t dataSize, uint32_t offset = 0);

    /// <summary>
    /// get a buffers data can only be done for cpu buffers
    /// </summary>
    void* getCPUMutUniformBufferData(UniformBufferID buffer);
    void* getCPUMutVertexBufferData(VertexBufferID buffer);
    void* getCPUMutIndexBufferData(IndexBufferID buffer);


    uint32_t getInstanceCount(VertexBufferID vertexBuffer);

}