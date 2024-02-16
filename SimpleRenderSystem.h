#pragma once

#include "GameDevice.h"
#include "GameObject.h"
#include "Gamepipeline.h"
#include "GameCamera.h"
// std
#include <memory>
#include <vector>

namespace misc {
	class SimpleRenderSystem {
	public:
		SimpleRenderSystem(GameDevice& device, VkRenderPass renderPass);
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		void renderGameObjects(VkCommandBuffer commandBuffer,
			std::vector<GameObject>& gameObjects,
			const GameCamera& camera);

	private:
		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);

		GameDevice& myDevice;

		std::unique_ptr<GamePipeline> myPipeline;
		VkPipelineLayout pipelineLayout;
	};
}  // namespace lve