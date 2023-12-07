#pragma once
#include <pch.h>
#include <VulkanRenderer/VulkanRenderer.h>

namespace MZ {

	extern VmaAllocator allocator;
	extern VkDevice device;

	struct VulkanShader {

		void cleanup() {
			vkDestroyPipeline(device, graphicsPipeline, nullptr);
			vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
			vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
		}

		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;
	};

}