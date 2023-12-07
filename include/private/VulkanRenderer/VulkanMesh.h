#pragma once
#include <pch.h>
#include <VulkanRenderer/VulkanRenderer.h>


namespace MZ {

	extern VmaAllocator allocator;

	struct VulkanMesh
	{

		void cleanup() {
			vmaDestroyBuffer(allocator, indexBuffer, indexBufferMemory);
			vmaDestroyBuffer(allocator, vertexBuffer, vertexBufferMemory);
		}

		VkBuffer vertexBuffer;
		VmaAllocation vertexBufferMemory;
		VkBuffer indexBuffer;
		VmaAllocation indexBufferMemory;
		uint32_t indicesSize;
	};

}