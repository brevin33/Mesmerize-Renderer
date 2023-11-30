#pragma once
#include <pch.h>
namespace MZ {

	struct VulkanRenderObject {

		~VulkanRenderObject() {
			vkDestroyDescriptorPool(*device, descriptorPool, nullptr);
			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				vkDestroyBuffer(*device, uniformBuffers[i], nullptr);
				vkFreeMemory(*device, uniformBuffersMemory[i], nullptr);
			}
		}

		MeshId meshId;
		ShaderId shaderId;

		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;
		VkDevice* device;
	};
}