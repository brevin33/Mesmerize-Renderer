#include <GLFW/glfw3.h>
#include <Renderer.h>
#define WIDTH 1920
#define HEIGHT 1080
#define VULKANRENDERER


void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);

	MZ::Mesh mesh;
	mesh.makeCircle(3);
	MZ::addMesh(&mesh, "../../../shaders/planetVert.spv", "../../../shaders/planetFrag.spv");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);

}