#pragma once
#include <VulkanRenderer/VulkanRenderer.h>

namespace MZ {

	struct VulkanTexture
	{
		void cleanup() {
			vmaDestroyImage(allocator, textureImage, textureImageMemory);
			vkDestroySampler(device, textureSampler, nullptr);
			vkDestroyImageView(device, textureImageView, nullptr);
		}

		VkImage textureImage;
		VmaAllocation textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

	};

}