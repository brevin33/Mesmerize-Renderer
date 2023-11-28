#pragma once
#include <pch.h>
namespace MZ {

	struct VulkanRenderObject {
		VMeshId meshId;
		VShaderId shaderId;

		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;
		VkDevice* device;
	};
}