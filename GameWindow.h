#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace misc {
	class GameWindow
	{
	public:
		GameWindow(int width, int height, std::string windowName);
		~GameWindow();

		bool shouldClose();
		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(width) }; }
		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	private:
		int width;
		int height;
		std::string windowName;
		GLFWwindow* window;

		void initWindow();
	};
}


