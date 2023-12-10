#include <GLFW/glfw3.h>

#define VULKANRENDERER
#include <Mesmerize/Renderer.h>
#define WIDTH 1920
#define HEIGHT 1080

void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);

	MZ::Model m("../../../models/backpack/backpack.obj");

	MZ::addModel(m, "../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv");
	MZ::addModel(m, "../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);

}