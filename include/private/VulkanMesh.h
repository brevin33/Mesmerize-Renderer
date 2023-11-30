#pragma once

namespace MZ {
	struct VulkanMesh
	{


		~VulkanMesh() {
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

}