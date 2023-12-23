#pragma once
#ifdef VULKANRENDERER

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

#include <pch.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <VulkanRenderer/VulkanEXT.h>
#include <stb_image.h>
#include <Mesmerize/Renderer.h>


#define MAX_COMMANDS 200

namespace MZ {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> computeFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value() && computeFamily.has_value();
        }

        bool uniqueFamily(uint32_t family) {
            return family != graphicsFamily && family != presentFamily && family != computeFamily;
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    enum BufferMappingType {
        NoMapping,
        Mapping,
        PersitantMapping,
    };

    GLFWwindow* window;
    bool framebufferResized = false;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VmaAllocator allocator;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkQueue computeQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;

    VkCommandPool commandPool;
    VkCommandPool computeCommandPool;


    std::array<VkCommandBuffer,MAX_FRAMES_IN_FLIGHT> commandBuffers;
    std::array<VkCommandBuffer, MAX_FRAMES_IN_FLIGHT> computeCommandBuffers;


    std::array<VkBuffer, MAX_FRAMES_IN_FLIGHT> drawCommandBuffer;
    std::array<VmaAllocation, MAX_FRAMES_IN_FLIGHT> drawCommandBufferMemory;
    std::array<VmaAllocationInfo, MAX_FRAMES_IN_FLIGHT> drawCommandBufferMapped;

    VkImage depthImage;
    VmaAllocation depthImageMemory;
    VkImageView depthImageView;

    std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> imageAvailableSemaphores;
    std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> renderFinishedSemaphores;
    std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> computeFinishedSemaphores;
    std::array<VkFence, MAX_FRAMES_IN_FLIGHT> inFlightFences;
    std::array<VkFence, MAX_FRAMES_IN_FLIGHT> computeInFlightFences;
    uint32_t currentFrame = 0;

    VkImage colorImage;
    VmaAllocation colorImageMemory;
    VkImageView colorImageView;
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

    const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    std::vector<UniformBufferID> mutUniformBuffers;
    std::vector<VertexBufferID> mutVertexBuffers;
    std::vector<IndexBufferID> mutIndexBuffers;

    std::vector<UniformBufferID> mutGPUUniformBuffers;
    std::vector<VertexBufferID> mutGPUVertexBuffers;
    std::vector<IndexBufferID> mutGPUIndexBuffers;

    std::vector<UniformBufferID> constUniformBuffers;
    std::vector<VertexBufferID> constVertexBuffers;
    std::vector<IndexBufferID> constIndexBuffers;

    // should index by RenderObjectID
    struct RenderObject {
        MaterialID material;
        VertexBufferID vertexBuffer;
        IndexBufferID indexBuffer;
        VertexBufferID instanceBuffer;
        uint8_t numVertexBuffers;
    };
    std::vector<RenderObject> renderObjects;

    // should index by ComputeID
    struct Compute {
        ComputeShaderID shaderID;
        uint32_t x;
        uint32_t y;
        uint32_t z;
        std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> descriptorSets;
    };
    std::vector<Compute> computes;

    //should index by ComputeShaderID
    std::vector<VkDescriptorSetLayout> computeDescriptorSetLayout;
    std::vector<VkPipelineLayout> computePipelineLayout;
    std::vector<VkPipeline> computePipeline;
    std::vector<VkDescriptorPool> computeDescriptorPool;

    // should index by UniformBufferID
    std::vector<std::array<VkBuffer, MAX_FRAMES_IN_FLIGHT>> uniformBuffers;
    std::vector<std::array<VmaAllocation, MAX_FRAMES_IN_FLIGHT>> uniformBuffersMemory;
    std::vector<std::array<VmaAllocationInfo,MAX_FRAMES_IN_FLIGHT>> uniformBuffersMapped;
    std::vector<void*> uniformBufferData;
    std::vector<uint32_t> uniformBuffersSize;
    std::vector<uint8_t> uniformUpToDate;

    // should index by VertexBufferID
    std::vector<std::array<VkBuffer, MAX_FRAMES_IN_FLIGHT>> vertexBuffers;
    std::vector<std::array<VmaAllocation, MAX_FRAMES_IN_FLIGHT>> vertexBufferMemorys;
    std::vector<std::array<VmaAllocationInfo, MAX_FRAMES_IN_FLIGHT>> vertexBuffersMapped;
    std::vector<void*> vertexBufferData;
    std::vector<uint32_t> vertexNumInstances;
    std::vector<uint64_t> vertexBuffersSize;
    std::vector<uint8_t> vertexUpToDate;

    // should index by IndexBufferID
    std::vector<std::array<VkBuffer, MAX_FRAMES_IN_FLIGHT>> indexBuffers;
    std::vector<std::array<VmaAllocation, MAX_FRAMES_IN_FLIGHT>> indexBufferMemorys;
    std::vector<std::array<VmaAllocationInfo, MAX_FRAMES_IN_FLIGHT>> indexBuffersMapped;
    std::vector<void*> indexBufferData;
    std::vector<uint32_t> indexBuffersSize;
    std::vector<uint32_t> indexNumIndices;
    std::vector<uint8_t> indexUpToDate;

    //should index by MaterialID
    std::vector<ShaderID> materialShaderIDs;
    std::vector<std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT>> materialDescriptorSets;

    // should index by ShaderID
    std::vector<VkPipelineLayout> shaderPipelineLayouts;
    std::vector<VkPipeline> shaderGraphicsPipelines;
    std::vector<VkDescriptorSetLayout> shaderDescriptorSetLayouts;
    std::vector<VkDescriptorPool> shaderDescriptorPools;

    // should index by TextureID
    std::vector<VkImage> textureImages;
    std::vector<VmaAllocation> textureImageMemorys;
    std::vector<VkImageView> textureImageViews;
    std::vector<VkSampler> textureSamplers;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
    };

    void drawObjects(VkCommandBuffer& commandBuffer, uint32_t renderFrame);

    void recreateSwapChain();

    void cleanupSwapChain();

    void createTextureSampler(VkSampler& textureSampler);
        
    void createTextureImage(std::string filepath, VmaAllocation& textureImageMemory, VkImage& textureImage, VkImageView& textureImageView);

    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels = 1);

    bool hasStencilComponent(VkFormat format);

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, uint32_t renderFrame);

    void recordComputeCommandBuffer(VkCommandBuffer commandBuffer);

    void createDrawCommandBuffer();

    void createDescriptorPool(VkDescriptorPool& descriptorPool, uint32_t poolSize, int numTextures, uint32_t numBuffers, uint32_t numStorageBuffers, uint32_t numStorageIamges, bool hasDrawCommandBuffer);

    void createDescriptorSets(std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT>& descriptorSets, VkDescriptorPool& descriptorPool, VkDescriptorSetLayout& descriptorSetLayout, TextureID* textureIDs, uint32_t numTextureIDs, UniformBufferID* bufferIDs, uint32_t numBuffers,
        UniformBufferID* storageUniforms, uint32_t numStorageUniforms, VertexBufferID* storageVertex, uint32_t numStorageVertex, IndexBufferID* storageIndex, uint32_t numStorageIndex, bool hasDrawCommandBuffer);

    void createGraphicsPipline(std::string vertShaderPath, std::string fragShaderPath, VkPipelineLayout& pipelineLayout, VkPipeline& graphicsPipeline, VkDescriptorSetLayout& descriptorSetLayout, VertexValueType* vertexValues, uint32_t numVertexValues, VertexValueType* InstanceTypes, uint32_t numInstanceTypes);

    void createDescriptorSetLayout(VkDescriptorSetLayout& descriptorSetLayout, int numTextures, uint32_t numBuffers);

    void createIndexBuffer(uint32_t* indices, VkBuffer& indexBuffer, VmaAllocation& indexBufferMemory, uint32_t numIndices);

    void createVertexBuffer(void* vertices, VkBuffer& vertexBuffer, VmaAllocation& vertexBufferMemory, VkDeviceSize bufferSize);

    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VmaAllocation& bufferMemory, BufferMappingType mapping, VmaAllocationInfo* allocationInfo = nullptr);

    void createComputeDescriptorSetLayout(VkDescriptorSetLayout& descriptorSetLayout, uint32_t numUbos, uint32_t numImages, uint32_t numStorageBuffer, uint32_t numStorageImages, bool hasDrawCommandBuffer);

    void createComputePipeline(std::string computeShaderFilePath, VkDescriptorSetLayout& descriptorSetLayout, VkPipelineLayout& pipleineLayout, VkPipeline& pipeline);

    VkCommandBuffer beginSingleTimeCommands();

    void createGPUSideOnlyBuffer(void* data, uint64_t dataSize, VkDeviceSize bufferSize, VkBuffer& buffer, VmaAllocation& bufferMemory, VkBufferUsageFlags useageFlags);

    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    std::array<uint32_t, 3> getOffsetVertexValue(VertexValueType vertexValue);

    VkVertexInputBindingDescription getBindingDescription(VertexValueType* VertexValues, uint32_t numVertexValues, VkVertexInputRate inputRate, uint32_t binding);

    std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(VertexValueType* VertexValues, uint32_t numVertexValues, uint32_t binding, uint32_t layoutOffset);

    static std::vector<char> readFile(const std::string& filename);

    VkShaderModule createShaderModule(const std::vector<char>& code);

    void createSyncObjects();

    void createVmaAllocator();

    void createCommandBuffers();

    void createFramebuffers();

    void createCommandPool();

    void createColorResources();

    void createDepthResources();

    VkFormat findDepthFormat();

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VmaAllocation& imageMemory);

    void createRenderPass();

    void createComputeCommandBuffers();

    void createSwapChain();

    bool isPowerOf2(uint32_t num);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    void createImageViews();

    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

    void createLogicalDevice();

    void pickPhysicalDevice();

    VkSampleCountFlagBits getMaxUsableSampleCount();

    bool isDeviceSuitable(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void setupDebugMessenger();

    void createSurface();

    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    int64_t ratePhysicalDevice(VkPhysicalDevice phDevice);

    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();

    void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

}



#endif 