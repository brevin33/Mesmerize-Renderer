#include <GenericRenderer/defaultPrivate.h>
#include <Mesmerize/defaults.h>

namespace MZ {

	UniformBufferID mainCameraBuffer;
	UniformBufferID cullingBuffer;
	ComputeShaderID cullingShader;
	ComputeID mainCullingCompute;

	void setup(GLFWwindow* window) {
		setupNoDefaults(window);
		setupDefaults();
	}

	void setupDefaults() {
		createMainCameraBuffer();
		createCullingBuffer();
		cullingShader = createComputeShader("../../../shaders/culling.spv", 1, 2, 0, 0, 0, true);
		mainCullingCompute = createCullingCompute(mainCameraBuffer);

	}

	void createMainCameraBuffer() {
		glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), MZ::getRenderWidth() / (float)MZ::getRenderHeight(), 0.1f, 10.0f);
		proj[1][1] *= -1;
		view = proj * view;
		mainCameraBuffer = createCPUMutUniformBuffer(&view, sizeof(glm::mat4));
	}
	
	void createCullingBuffer() {
		glm::vec4 defaultSphere(0,0,0,-1);
		std::vector<glm::vec4> defaultSpheres(MAX_COMMANDS, defaultSphere);
		cullingBuffer = createCPUMutUniformBuffer(defaultSpheres.data(), sizeof(glm::vec4) * MAX_COMMANDS);
	}

	ComputeID createCullingCompute(UniformBufferID cameraBuffer) {
		std::array<UniformBufferID, 2> cullingUniformBuffers = { cullingBuffer, cameraBuffer };
		return addCompute(cullingShader, MAX_COMMANDS/128, 1, 1, cullingUniformBuffers.data(), 2, nullptr, 0, nullptr, 0, nullptr, 0, nullptr, 0, true);
	}

	void addToCullingBuffer(BoundingSphere& boundingSphere, RenderObjectID renderObjectID) {
		updateCPUMutUniformBuffer(cullingBuffer, &boundingSphere, sizeof(glm::vec4), renderObjectID * sizeof(glm::vec4));
	}

}