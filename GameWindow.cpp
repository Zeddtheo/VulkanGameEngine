#include "GameWindow.h"
#include <stdexcept>

namespace misc {
	GameWindow::GameWindow(int width, int height, std::string windowName):width(width), height(height), windowName(windowName) {
		initWindow();
	}

	GameWindow::~GameWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void GameWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	}

	bool GameWindow::shouldClose() {
		return glfwWindowShouldClose(window);
	}

	void GameWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void GameWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		auto myWindow = reinterpret_cast<GameWindow*>(glfwGetWindowUserPointer(window));
		myWindow->framebufferResized = true;
		myWindow->width = width;	
		myWindow->height = height;
	}
}