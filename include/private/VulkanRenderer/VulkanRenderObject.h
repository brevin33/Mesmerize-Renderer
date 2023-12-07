#pragma once
#include <pch.h>
#include <VulkanRenderer/VulkanRenderer.h>


namespace MZ {
	extern VmaAllocator allocator;
	extern VkDevice device;

	struct VulkanRenderObject
	{


		void cleanup() {
			vkDestroyDescriptorPool(device, descriptorPool, nullptr);
			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				vmaDestroyBuffer(allocator, uniformBuffers[i], uniformBuffersMemory[i]);
			}
		}

		MeshID meshID;
		ShaderID shaderID;
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VmaAllocation> uniformBuffersMemory;
		std::vector<VmaAllocationInfo> uniformBuffersMapped;
	};

}