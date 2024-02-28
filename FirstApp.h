#pragma once

#include "GameDevice.h"
#include "GameObject.h"
#include "GameRenderer.h"
#include "GameWindow.h"
#include "Descriptors.h"

#include <memory>
#include <vector>

namespace misc {
class FirstApp
{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp &operator=(const FirstApp&) = delete;

		void run();
	private:
		void loadGameObjects();

		GameWindow myWindow{ WIDTH, HEIGHT, "Hello, Vulkan!" };
		GameDevice myDevice{ myWindow };
		GameRenderer myRenderer{myWindow, myDevice};
		// note: order of declarations matters
		std::unique_ptr<DescriptorPool> globalPool{};
		GameObject::Map gameObjects;
};
}


