#include <GLFW/glfw3.h>
#include <Mesmerize/Renderer.h>
#include <Mesmerize/Vertex.h>
#include "Model.h"

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;


void spin(ObjectID id) {
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	MZ::UniformBufferObject ubo{};
	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	MZ::updateUBO(id,ubo);
}


void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);
	ShaderID shaderID = MZ::createShader("../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv", 1);

	Model m("../../../models/backpack/backpack.obj");
	std::vector<ObjectID> backpack = m.addToRenderer(shaderID);
	m.unload();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		for (size_t i = 0; i < backpack.size(); i++)
		{
			spin(backpack[i]);
		}
		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);
}