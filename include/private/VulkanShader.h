#pragma once
namespace MZ {
	struct VulkanShader {

		~VulkanShader() {
			vkDestroyPipeline(*device, graphicsPipeline, nullptr);
			vkDestroyPipelineLayout(*device, pipelineLayout, nullptr);
			vkDestroyDescriptorSetLayout(*device, descriptorSetLayout, nullptr);

		}

		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;
		VkDevice* device;
	};
}