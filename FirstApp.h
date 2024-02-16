#pragma once

#include "GameDevice.h"
#include "GameObject.h"
#include "GameRenderer.h"
#include "GameWindow.h"

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
		std::vector<GameObject> gameObjects;
};
}


