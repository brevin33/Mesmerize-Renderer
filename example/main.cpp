#include <GLFW/glfw3.h>
#include <Renderer.h>
#include <Model.h>
#define WIDTH 1920
#define HEIGHT 1080
#define VULKANRENDERER


void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);

	std::vector<MZ::Vertex> vertices;
	std::vector<uint32_t> indices;
	MZ::makeCircle(1,vertices, indices);
	MZ::Model m("../../../models/backpack/backpack.obj");

	MZ::addModel(m, "../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);

}