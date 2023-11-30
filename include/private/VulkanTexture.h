#pragma once

struct VulkanTexture {

    ~VulkanTexture() {
        vkDestroySampler(*device, textureSampler, nullptr);
        vkDestroyImageView(*device, textureImageView, nullptr);
        vkDestroyImage(*device, textureImage, nullptr);
        vkFreeMemory(*device, textureImageMemory, nullptr);
    }

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkDevice* device;
};