#include <GLFW/glfw3.h>
#include <Renderer.h>
#define WIDTH 1920
#define HEIGHT 1080

void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

	MZ::Renderer mezmerize(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		mezmerize.drawFrame();
	}
	glfwDestroyWindow(window);

}