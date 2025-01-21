#define GLFW_INCLUDE_VULKAN
#include "VulkanRenderer.h"
#include <glfw3.h>
#include <stdexcept>
#include <vector>
#include <string>
using std::string;

GLFWwindow* window = nullptr;
VulkanRenderer vulkanRenderer;

void initWindow(string wName = "Vulkan", const int width = 800, const int height = 600)
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Glfw won't work with opengl
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

void clean()
{
	vulkanRenderer.clean();
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main()
{
	initWindow();
	if (vulkanRenderer.init(window) == EXIT_FAILURE) return EXIT_FAILURE;
	while (!glfwWindowShouldClose(window))
	{
		vulkanRenderer.draw();
		glfwPollEvents();
	}
	clean();
	return 0;
}