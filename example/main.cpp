#include <GLFW/glfw3.h>
#include <Mesmerize/Renderer.h>
#include "Model.h"

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

struct UniformBufferObject {
	glm::mat4 model;
};


void spin(MZ::RenderObject object) {
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	UniformBufferObject ubo{};
	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	updateRenderObjectData(object, &ubo, sizeof(ubo));
}


void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);

	Model m("../../../models/backpack/backpack.obj");
	std::vector<MZ::RenderObject> backpack = m.addToRenderer();
	m.unload();

	auto i = sizeof(Vertex);

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