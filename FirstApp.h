#pragma once
#include "GameWindow.h"
#include "GamePipeline.h"
#include "GameEngineDevice.h"

#include <memory>
#include <vector>
#include "GameEngineSwapChain.h"
#include "GameModel.h"

namespace misc {
class FirstApp
{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();
	private:
		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		void sierpinski(std::vector<GameModel::Vertex>& vertices,
			int depth,
			glm::vec2 left,
			glm::vec2 right,
			glm::vec2 top);

		GameWindow gameWindow{ WIDTH, HEIGHT, "Hello, Vulkan!" };
		GameEngineDevice myDevice{ gameWindow };
		GameEngineSwapChain mySwapChain{myDevice, gameWindow.getExtent() };

		std::unique_ptr<GamePipeline> myPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<GameModel> gameModel;
};
}


