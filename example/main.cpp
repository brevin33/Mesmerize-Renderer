#include <GLFW/glfw3.h>
#include <Mesmerize/Renderer.h>
#include "Model.h"

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;



void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);
	ShaderID shaderID = MZ::createShader("../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv", 1);

	Model m("../../../models/backpack/backpack.obj");
	m.addToRenderer(shaderID);
	m.unload();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);
}