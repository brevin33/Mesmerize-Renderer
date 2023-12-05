#pragma once
#include <pch.h>

struct VulkanMesh
{

	void cleanup() {
		vkDestroyBuffer(*device, indexBuffer, nullptr);
		vkFreeMemory(*device, indexBufferMemory, nullptr);

		vkDestroyBuffer(*device, vertexBuffer, nullptr);
		vkFreeMemory(*device, vertexBufferMemory, nullptr);
	}

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	VkDevice* device;
	uint32_t indicesSize;
};